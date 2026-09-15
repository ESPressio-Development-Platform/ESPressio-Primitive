#!/usr/bin/env python3
"""Tranche 11 V11-02: validate production-source predecessor eradication.

This gate deliberately scans only production/public source roots. Examples, demos,
README/wiki/documentation and generated CI fixtures belong to V11-03 and are not
used as V11-02 evidence.

The scan is comment-aware: architectural comments may name predecessor APIs when
explaining their removal, while executable/declarative source may not consume them.
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

# Symbols/types that the locked redesign explicitly removes rather than preserving
# through compatibility aliases, wrappers or facades.  Keep this list identifier-
# based so similarly worded prose or unrelated identifiers do not become failures.
REMOVED_IDENTIFIERS = (
    "PrecisionThread",
    "PrecisionEventThread",
    "EventThreadBase",
    "EventTransportManager",
    "EventManager",
    "EventManagerObservable",
    "IEventManagerObserver",
    "EventDispatcher",
    "EventReceiver",
    "EventListener",
    "EventPriority",
    "EventDispatchMethod",
    "EventListenerInterest",
    "CommandRegistry",
    "CommandRegistryEventBridge",
    "RemoteStateObserverThread",
    "StateEpoch",
    "RadioWorker",
    "ThreadManager",
    "ThreadTerminationDispatcher",
    "PrecisionScheduler",
    "DesiredIterationPeriod",
    "ClockSynchronizationState",
)

REMOVED_PATTERNS = {
    identifier: re.compile(rf"\b{re.escape(identifier)}\b")
    for identifier in REMOVED_IDENTIFIERS
}

SOURCE_SUFFIXES = {
    ".h", ".hpp", ".hh", ".hxx", ".c", ".cc", ".cpp", ".cxx", ".ipp", ".tpp", ".inc"
}


def strip_cpp_comments(text: str) -> str:
    """Strip C/C++ comments while preserving literals and line positions."""
    output: list[str] = []
    index = 0
    state = "code"
    quote = ""

    while index < len(text):
        current = text[index]
        following = text[index + 1] if index + 1 < len(text) else ""

        if state == "code":
            if current == "/" and following == "/":
                state = "line-comment"
                output.extend((" ", " "))
                index += 2
                continue
            if current == "/" and following == "*":
                state = "block-comment"
                output.extend((" ", " "))
                index += 2
                continue
            if current in {'"', "'"}:
                state = "literal"
                quote = current
            output.append(current)
            index += 1
            continue

        if state == "line-comment":
            if current == "\n":
                state = "code"
                output.append("\n")
            else:
                output.append(" ")
            index += 1
            continue

        if state == "block-comment":
            if current == "*" and following == "/":
                state = "code"
                output.extend((" ", " "))
                index += 2
                continue
            output.append("\n" if current == "\n" else " ")
            index += 1
            continue

        output.append(current)
        if current == "\\" and index + 1 < len(text):
            output.append(text[index + 1])
            index += 2
            continue
        if current == quote:
            state = "code"
            quote = ""
        index += 1

    return "".join(output)


def production_files(repo: Path):
    for root_name in ("src", "include"):
        root = repo / root_name
        if not root.exists():
            continue
        for path in root.rglob("*"):
            if path.is_file() and path.suffix.lower() in SOURCE_SUFFIXES:
                yield path


def line_number(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    scanned_files = 0

    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue

        for path in production_files(repo):
            scanned_files += 1
            try:
                original = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                errors.append(f"{path.relative_to(root)}: production source is not UTF-8 text")
                continue
            source = strip_cpp_comments(original)
            for identifier, pattern in REMOVED_PATTERNS.items():
                match = pattern.search(source)
                if match:
                    errors.append(
                        f"{path.relative_to(root)}:{line_number(source, match.start())}: "
                        f"removed predecessor identifier {identifier}"
                    )

    if errors:
        print("V11-02 production-source eradication FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        f"V11-02 production-source eradication passed across {len(REPOSITORIES)} repositories "
        f"and {scanned_files} production/public source files."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
