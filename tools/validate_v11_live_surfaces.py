#!/usr/bin/env python3
"""Tranche 11 V11-03: audit live instructional/example/CI surfaces.

V11-02 owns production source/include eradication. This gate deliberately targets
examples/demos, live README/docs/wiki/API maps and generated CI fixture code.
Historical CHANGELOGs and tranche/history reports are not live API instructions.

For Markdown we validate fenced code and positive instructional inline API spelling.
Inline identifiers inside explicit removal/negative architecture prose are allowed: a
README should be able to say that `PrecisionThread` no longer exists without that
statement being mistaken for a usage example.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPOSITORIES = (
    "Primitive", "System", "Serializable", "Persistence", "Task", "Timing",
    "Threads", "Event", "Command", "State", "Adapters", "Radio", "Mesh",
    "MeshAdapters", "RadioAdapters", "Sockets", "Serial", "WiFi", "ESP32",
    "Logging", "Security", "Units", "Observable", "Web", "Lua", "NRF24",
)

REMOVED_IDENTIFIERS = (
    "PrecisionThread", "PrecisionEventThread", "EventThreadBase",
    "EventTransportManager", "EventManager", "EventManagerObservable",
    "IEventManagerObserver", "EventDispatcher", "EventReceiver", "EventListener",
    "EventPriority", "EventDispatchMethod", "EventListenerInterest",
    "CommandRegistry", "CommandRegistryEventBridge", "RemoteStateObserverThread",
    "StateEpoch", "RadioWorker", "ThreadManager", "ThreadTerminationDispatcher",
    "PrecisionScheduler", "DesiredIterationPeriod", "ClockSynchronizationState",
)
REMOVED_PATTERNS = {
    name: re.compile(rf"\b{re.escape(name)}\b") for name in REMOVED_IDENTIFIERS
}

STALE_BRANCH = re.compile(
    r"ESPressio-Development-Platform/ESPressio-[A-Za-z0-9-]+\.git#"
    r"(?!primitives_redesign(?:[\"'\s)`]|$))([A-Za-z0-9_./-]+)"
)

SOURCE_SUFFIXES = {".h", ".hpp", ".hh", ".hxx", ".c", ".cc", ".cpp", ".cxx", ".ino", ".ipp", ".tpp", ".inc"}
MARKDOWN_SUFFIXES = {".md", ".markdown"}
WORKFLOW_SUFFIXES = {".yml", ".yaml"}

HISTORICAL_NAME_PARTS = (
    "changelog", "history", "tranche_handoff", "tranche_", "implementation_report",
    "closure", "resource_accounting", "migration_report",
)

NEGATIVE_ARCHITECTURE_PHRASES = (
    "no ", "no longer", "does not", "doesn't", "do not", "don't", "not retained",
    "not exist", "removed", "removal", "predecessor", "legacy", "obsolete", "replaced",
    "without ", "rather than", "instead of",
)


def strip_cpp_comments(text: str) -> str:
    out: list[str] = []
    i = 0
    state = "code"
    quote = ""
    while i < len(text):
        c = text[i]
        n = text[i + 1] if i + 1 < len(text) else ""
        if state == "code":
            if c == "/" and n == "/":
                state = "line"
                out.extend((" ", " "))
                i += 2
                continue
            if c == "/" and n == "*":
                state = "block"
                out.extend((" ", " "))
                i += 2
                continue
            if c in {'"', "'"}:
                state, quote = "literal", c
            out.append(c)
            i += 1
            continue
        if state == "line":
            if c == "\n":
                state = "code"
                out.append("\n")
            else:
                out.append(" ")
            i += 1
            continue
        if state == "block":
            if c == "*" and n == "/":
                state = "code"
                out.extend((" ", " "))
                i += 2
                continue
            out.append("\n" if c == "\n" else " ")
            i += 1
            continue
        out.append(c)
        if c == "\\" and i + 1 < len(text):
            out.append(text[i + 1])
            i += 2
            continue
        if c == quote:
            state, quote = "code", ""
        i += 1
    return "".join(out)


def live_markdown(path: Path, repo: Path) -> bool:
    rel = path.relative_to(repo)
    lower_name = path.name.lower()
    if any(part in lower_name for part in HISTORICAL_NAME_PARTS):
        return False
    return (
        path.name.lower().startswith("readme")
        or (rel.parts and rel.parts[0].lower() in {"docs", "doc", "wiki", "api"})
        or "examples" in {p.lower() for p in rel.parts}
        or "demos" in {p.lower() for p in rel.parts}
    )


def markdown_instructional_code(text: str) -> str:
    pieces: list[str] = []
    # Fenced blocks are always copyable/instructional surfaces.
    for match in re.finditer(r"```[^\n]*\n(.*?)```", text, flags=re.DOTALL):
        pieces.append(match.group(1))

    # Inline API spelling is instructional unless its containing line explicitly says
    # that the API is absent/removed/replaced.  Preserve blank placeholders so line
    # numbers remain reasonably diagnostic.
    for line in text.splitlines():
        lower = line.lower()
        negative = any(phrase in lower for phrase in NEGATIVE_ARCHITECTURE_PHRASES)
        if negative:
            pieces.append("")
            continue
        inline = [m.group(1) for m in re.finditer(r"(?<!`)`([^`\n]+)`(?!`)", line)]
        pieces.append(" ".join(inline))
    return "\n".join(pieces)


def is_guard_line(line: str) -> bool:
    lower = line.lower()
    guard_words = ("grep ", "rg ", "forbidden", "legacy", "removed", "predecessor", "obsolete", "reject")
    return any(word in lower for word in guard_words)


def report_identifiers(text: str, label: str, errors: list[str]) -> None:
    for name, pattern in REMOVED_PATTERNS.items():
        match = pattern.search(text)
        if match:
            line = text.count("\n", 0, match.start()) + 1
            errors.append(f"{label}:{line}: live surface teaches removed identifier {name}")


def scan_repo(repo: Path, root: Path, errors: list[str]) -> tuple[int, int, int]:
    example_files = markdown_files = workflow_files = 0

    for tree_name in ("examples", "demos", "demo"):
        tree = repo / tree_name
        if not tree.exists():
            continue
        for path in tree.rglob("*"):
            if not path.is_file() or path.suffix.lower() not in SOURCE_SUFFIXES:
                continue
            example_files += 1
            try:
                text = strip_cpp_comments(path.read_text(encoding="utf-8"))
            except UnicodeDecodeError:
                continue
            report_identifiers(text, str(path.relative_to(root)), errors)
            for match in STALE_BRANCH.finditer(text):
                errors.append(f"{path.relative_to(root)}: stale coordinated branch #{match.group(1)}")

    for path in repo.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in MARKDOWN_SUFFIXES or not live_markdown(path, repo):
            continue
        markdown_files += 1
        try:
            text = path.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            continue
        report_identifiers(markdown_instructional_code(text), str(path.relative_to(root)), errors)
        for match in STALE_BRANCH.finditer(text):
            errors.append(f"{path.relative_to(root)}: stale coordinated branch #{match.group(1)}")

    workflows = repo / ".github" / "workflows"
    if workflows.exists():
        for path in workflows.rglob("*"):
            if not path.is_file() or path.suffix.lower() not in WORKFLOW_SUFFIXES:
                continue
            workflow_files += 1
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                continue
            for match in STALE_BRANCH.finditer(text):
                errors.append(f"{path.relative_to(root)}: stale coordinated branch #{match.group(1)}")
            for number, line in enumerate(text.splitlines(), 1):
                if is_guard_line(line):
                    continue
                if not any(marker in line for marker in ("#include", "using ", "class ", "struct ", "public ", "private ", "protected ", "::", "<", ">", "(")):
                    continue
                for name, pattern in REMOVED_PATTERNS.items():
                    if pattern.search(line):
                        errors.append(f"{path.relative_to(root)}:{number}: generated/live CI fixture uses removed identifier {name}")

    return example_files, markdown_files, workflow_files


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    totals = [0, 0, 0]
    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue
        counts = scan_repo(repo, root, errors)
        totals = [a + b for a, b in zip(totals, counts)]

    if errors:
        print("V11-03 live-surface validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        "V11-03 active redesign live-surface scan passed across "
        f"{len(REPOSITORIES)} repositories: {totals[0]} example/demo source files, "
        f"{totals[1]} live Markdown/API files, {totals[2]} workflow files."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
