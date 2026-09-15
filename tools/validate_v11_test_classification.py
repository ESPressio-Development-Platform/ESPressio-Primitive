#!/usr/bin/env python3
"""Tranche 11 V11-06: classify every current test/validation artifact semantically.

This is deliberately stricter than counting tests.  Every file beneath a repository's
`tests`/`test` tree and every active GitHub Actions workflow is assigned to an explicit
redesign semantic domain.  Test sources that still exercise a removed predecessor API
must identify themselves as negative/eradication evidence; otherwise they fail the gate.

The audit does not claim that filename classification alone proves behavior.  It proves
that the complete current suite has been enumerated into the final architecture and that
no ordinary positive test silently remains coupled to predecessor surfaces.  Behavioral
proof stays with the repository tests and later V11 evidence gates.
"""

from __future__ import annotations

import re
import sys
from collections import Counter
from pathlib import Path

SEMANTIC_DOMAIN = {
    "Primitive": "primitive-metadata-policy",
    "System": "platform-abstraction-runtime-identity",
    "Serializable": "bounded-schema-codec",
    "Persistence": "durability-recovery-runtime-identity",
    "Task": "bounded-execution-admission",
    "Timing": "clock-discipline-qualified-time",
    "Threads": "single-root-thread-capabilities",
    "Event": "event-occurrence-lifetime-admission",
    "Command": "command-execution-response-replay",
    "State": "owner-truth-convergence-observation",
    "Adapters": "bounded-family-admission-qos",
    "Radio": "physical-radio-fragmentation-arbitration",
    "Mesh": "family-neutral-routing-admission",
    "MeshAdapters": "mesh-family-binding",
    "RadioAdapters": "direct-radio-family-binding",
    "Sockets": "socket-transport-integration",
    "Serial": "serial-tooling-diagnostics",
    "WiFi": "wifi-platform-domain",
    "ESP32": "esp32-provider-integration",
    "Logging": "bounded-diagnostics-logging",
    "Security": "security-authentication-provenance",
    "Units": "dependency-neutral-units",
    "Observable": "synchronous-observation",
    "Web": "web-dynamic-tooling",
    "Lua": "lua-dynamic-tooling",
    "NRF24": "nrf24-radio-provider",
}

REMOVED_IDENTIFIERS = (
    "PrecisionThread", "PrecisionEventThread", "EventThreadBase",
    "EventTransportManager", "EventManager", "EventManagerObservable",
    "IEventManagerObserver", "EventDispatcher", "EventReceiver", "EventListener",
    "EventPriority", "EventDispatchMethod", "EventListenerInterest",
    "CommandRegistry", "CommandRegistryEventBridge", "RemoteStateObserverThread",
    "StateEpoch", "RadioWorker", "ThreadManager", "ThreadTerminationDispatcher",
    "PrecisionScheduler", "DesiredIterationPeriod", "ClockSynchronizationState",
)
REMOVED = {name: re.compile(rf"\b{re.escape(name)}\b") for name in REMOVED_IDENTIFIERS}

TEST_SUFFIXES = {
    ".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx",
    ".py", ".sh", ".bash", ".cmake", ".yml", ".yaml", ".json", ".ini", ".txt",
}
SUPPORT_MARKERS = ("stub", "fixture", "fixtures", "mock", "fake", "support", "data", "vector")
NEGATIVE_MARKERS = (
    "negative", "compile_fail", "compile-fail", "eradication", "legacy", "removed",
    "predecessor", "forbidden", "must not", "must_not", "does not exist", "unavailable",
)


def is_negative_evidence(path: Path, text: str) -> bool:
    lower = f"{path.as_posix()}\n{text}".lower()
    return any(marker in lower for marker in NEGATIVE_MARKERS)


def artifact_kind(path: Path, root: Path) -> str:
    rel = path.relative_to(root)
    lower_parts = tuple(part.lower() for part in rel.parts)
    if lower_parts and lower_parts[0] == ".github":
        return "workflow"
    if path.name.lower() == "cmakelists.txt" or any(
        marker in part.lower() for part in rel.parts for marker in SUPPORT_MARKERS
    ):
        return "test-support"
    return "test-contract"


def discover_test_files(repo: Path):
    seen: set[Path] = set()
    for root_name in ("tests", "test"):
        root = repo / root_name
        if not root.exists():
            continue
        for path in root.rglob("*"):
            if not path.is_file() or path in seen:
                continue
            if path.name == "CMakeLists.txt" or path.suffix.lower() in TEST_SUFFIXES:
                seen.add(path)
                yield path

    workflows = repo / ".github" / "workflows"
    if workflows.exists():
        for path in workflows.rglob("*"):
            if path.is_file() and path.suffix.lower() in {".yml", ".yaml"} and path not in seen:
                seen.add(path)
                yield path


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    classified = 0
    predecessor_negative = 0
    counts: Counter[str] = Counter()

    for repo_name, domain in SEMANTIC_DOMAIN.items():
        repo = root / f"ESPressio-{repo_name}"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue

        for path in discover_test_files(repo):
            classified += 1
            kind = artifact_kind(path, repo)
            counts[f"{domain}:{kind}"] += 1
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                errors.append(f"{path.relative_to(root)}: non-UTF-8 test artifact cannot be semantically audited")
                continue

            hits = [name for name, pattern in REMOVED.items() if pattern.search(text)]
            if hits:
                if is_negative_evidence(path.relative_to(repo), text):
                    predecessor_negative += 1
                else:
                    errors.append(
                        f"{path.relative_to(root)}: ordinary {kind} in semantic domain '{domain}' "
                        f"uses removed predecessor identifier(s) {sorted(hits)} without negative/eradication intent"
                    )

    if classified == 0:
        errors.append("no current test/workflow artifacts were discovered")

    if errors:
        print("V11-06 semantic test classification FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    domains_with_evidence = len({key.split(":", 1)[0] for key in counts})
    print(
        f"V11-06 semantic test classification passed: {classified} test/workflow artifacts, "
        f"{domains_with_evidence} semantic domains with evidence, "
        f"{predecessor_negative} explicit predecessor-eradication artifacts."
    )
    for key in sorted(counts):
        print(f"  {key}: {counts[key]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
