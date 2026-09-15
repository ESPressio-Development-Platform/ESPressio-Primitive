#!/usr/bin/env python3
"""Validate locked Primitive-platform dependency and eradication boundaries.

This is intentionally a structural validator. Family/runtime behavioural semantics remain
owned and tested by their repositories; this script prevents cross-repository dependency,
branch, and removed-API drift from silently reintroducing predecessor architecture.

Private redesign repositories cannot be read by another repository's scoped GITHUB_TOKEN.
They are therefore named explicitly in SELF_GUARDED_REPOSITORIES and must carry the
same structural checks in their own repository-local workflow. They are never silently
omitted from the platform validation model.
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path
from typing import Iterable

REPOSITORIES = (
    "Primitive",
    "System",
    "Serializable",
    "Persistence",
    "Task",
    "Timing",
    "Threads",
    "Event",
    "Command",
    "State",
    "Adapters",
    "Radio",
    "Mesh",
    "MeshAdapters",
    "RadioAdapters",
    "Sockets",
    "Serial",
    "WiFi",
    "ESP32",
    "Logging",
    "Security",
    "Units",
    "Web",
    "Lua",
    "NRF24",
)

# ESPressio-ESP-Now is private. Its redesign boundary workflow runs inside that repository,
# where its repository-scoped token can read the source. Demos/Tree/Display/Labs are private
# too but are not part of this structural tranche.
SELF_GUARDED_REPOSITORIES = ("ESP-Now",)

DEPENDENCY_NEUTRAL = {"Primitive", "System", "Units"}

FORBIDDEN_DEPENDENCIES = {
    "System": {"Persistence"},
    "Timing": {"Threads", "Event", "Command", "State"},
    "Threads": {"Event", "Command", "State"},
    "Command": {"Event"},
    "State": {"Event", "Command"},
    "Adapters": {"Radio", "Event", "Command", "State", "Mesh"},
    "Radio": {"Primitive", "Event", "Command", "State", "Mesh", "Adapters", "RadioAdapters"},
    "Mesh": {"Event", "Command", "State", "MeshAdapters", "RadioAdapters"},
}

EXACT_DEPENDENCIES = {
    "Persistence": {"Serializable", "Security", "System"},
    "Adapters": {"System", "Primitive", "Task"},
}

REMOVED_PRODUCTION_TOKENS = (
    "PrecisionThread",
    "PrecisionEventThread",
    "EventThreadBase",
    "RemoteStateObserverThread",
    "EventTransportManager",
    "EventManagerObservable",
    "IEventManagerObserver",
    "EventPriority",
    "EventDispatchMethod",
    "EventListenerInterest",
    "CommandRegistryEventBridge",
    "ClockSynchronizationState",
    "StateEpoch",
)

# CommandRegistry is deliberately separate so the final descriptor/tooling vocabulary can
# use words such as registry only where it is not the removed dynamic semantic CommandRegistry.
REMOVED_COMMAND_REGISTRY = re.compile(r"\bCommandRegistry\b")
OBSOLETE_BRANCH = re.compile(
    r"ESPressio-Development-Platform/ESPressio-[A-Za-z0-9-]+\.git#"
    r"(?!primitives_redesign(?:[\"'\s]|$))([A-Za-z0-9_./-]+)"
)

CONFIG_NAMES = {"library.json", "library.properties", "platformio.ini", "CMakeLists.txt", "component.mk"}
CONFIG_SUFFIXES = {".yml", ".yaml"}
SOURCE_SUFFIXES = {".h", ".hpp", ".hh", ".c", ".cc", ".cpp", ".cxx", ".ino"}


def dependency_name(value: str) -> str:
    prefix = "ESPressio-"
    return value[len(prefix):] if value.startswith(prefix) else value


def manifest_dependencies(repo: Path) -> set[str] | None:
    manifest = repo / "library.json"
    if not manifest.exists():
        return None
    data = json.loads(manifest.read_text(encoding="utf-8"))
    raw = data.get("dependencies", [])
    if isinstance(raw, dict):
        names = raw.keys()
    elif isinstance(raw, list):
        names = (
            entry.get("name", "") if isinstance(entry, dict) else str(entry)
            for entry in raw
        )
    else:
        raise ValueError(f"{manifest}: unsupported dependencies value {type(raw).__name__}")
    return {dependency_name(name) for name in names if name}


def iter_files(repo: Path, roots: Iterable[str], suffixes: set[str] | None = None):
    for root_name in roots:
        root = repo / root_name
        if not root.exists():
            continue
        if root.is_file():
            candidates = (root,)
        else:
            candidates = root.rglob("*")
        for path in candidates:
            if not path.is_file():
                continue
            if ".git" in path.parts:
                continue
            if suffixes is not None and path.suffix.lower() not in suffixes:
                continue
            yield path


def check_manifests(root: Path, errors: list[str]) -> None:
    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            errors.append(f"missing checked-out public redesign repository: {repo.name}")
            continue
        try:
            dependencies = manifest_dependencies(repo)
        except Exception as exc:  # structural validation should report all errors together
            errors.append(str(exc))
            continue

        if dependencies is None:
            # Some adapter/integration repositories intentionally have no Arduino manifest.
            continue

        if name in DEPENDENCY_NEUTRAL and dependencies:
            errors.append(f"{repo.name}: must remain dependency-neutral, found {sorted(dependencies)}")

        forbidden = FORBIDDEN_DEPENDENCIES.get(name, set()) & dependencies
        if forbidden:
            errors.append(f"{repo.name}: forbidden dependency edge(s): {sorted(forbidden)}")

        expected = EXACT_DEPENDENCIES.get(name)
        if expected is not None and dependencies != expected:
            errors.append(
                f"{repo.name}: locked dependency set is {sorted(expected)}, found {sorted(dependencies)}"
            )


def check_branch_references(root: Path, errors: list[str]) -> None:
    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            continue
        candidates = []
        for path in repo.rglob("*"):
            if not path.is_file() or ".git" in path.parts:
                continue
            relative = path.relative_to(repo)
            is_config = path.name in CONFIG_NAMES or (
                relative.parts and relative.parts[0] == ".github" and path.suffix.lower() in CONFIG_SUFFIXES
            )
            if not is_config:
                continue
            candidates.append(path)

        for path in candidates:
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                continue
            for match in OBSOLETE_BRANCH.finditer(text):
                errors.append(
                    f"{path.relative_to(root)}: obsolete ESPressio branch reference #{match.group(1)}"
                )


def check_removed_production_apis(root: Path, errors: list[str]) -> None:
    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            continue
        for path in iter_files(repo, ("src", "examples"), SOURCE_SUFFIXES):
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                continue
            for token in REMOVED_PRODUCTION_TOKENS:
                if token in text:
                    errors.append(f"{path.relative_to(root)}: removed production API token {token}")
            if REMOVED_COMMAND_REGISTRY.search(text):
                errors.append(f"{path.relative_to(root)}: removed dynamic CommandRegistry API")


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    check_manifests(root, errors)
    check_branch_references(root, errors)
    check_removed_production_apis(root, errors)

    if errors:
        print("Primitive-platform structural validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        "Primitive-platform public structural validation passed: locked DAG, redesign branch refs, "
        "and removed production APIs remain clean."
    )
    print(
        "Private in-scope repository validation is explicit and repository-local: "
        + ", ".join(f"ESPressio-{name}" for name in SELF_GUARDED_REPOSITORIES)
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
