#!/usr/bin/env python3
"""Validate the final dynamic-tooling contracts across the redesign graph.

This is intentionally a cross-repository structural/semantic guard. Each tooling
repository retains its own executable behavioural tests; this validator proves that
the exact checked-out Web/Lua/Serial/WiFi tips still consume the final Primitive-family
surfaces without recreating predecessor registries, ownership or unbounded ingress.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def fail(errors: list[str], message: str) -> None:
    errors.append(message)


def read(root: Path, repository: str, relative: str, errors: list[str]) -> str:
    path = root / f"ESPressio-{repository}" / relative
    if not path.is_file():
        fail(errors, f"ESPressio-{repository}/{relative}: required tooling surface is missing")
        return ""
    try:
        return path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        fail(errors, f"ESPressio-{repository}/{relative}: required tooling surface is not UTF-8 text")
        return ""


def require(text: str, repository: str, relative: str, tokens: tuple[str, ...], errors: list[str]) -> None:
    for token in tokens:
        if token not in text:
            fail(errors, f"ESPressio-{repository}/{relative}: required final-contract token {token!r} is missing")


def forbid(text: str, repository: str, relative: str, tokens: tuple[str, ...], errors: list[str]) -> None:
    for token in tokens:
        if token in text:
            fail(errors, f"ESPressio-{repository}/{relative}: forbidden predecessor/ownership token {token!r} is present")


def require_file(root: Path, repository: str, relative: str, errors: list[str]) -> None:
    if not (root / f"ESPressio-{repository}" / relative).is_file():
        fail(errors, f"ESPressio-{repository}/{relative}: required focused validation evidence is missing")


def validate_active_docs(root: Path, errors: list[str]) -> None:
    # Canonical active guidance must point coordinated ESPressio dependencies at the redesign branch.
    # Historical development reports are deliberately outside this D10-20 active-document check.
    active = (
        ("Web", "README.md"),
        ("Lua", "README.md"),
        ("Lua", "docs/Integration.md"),
        ("Serial", "README.md"),
        ("WiFi", "README.md"),
    )
    stale_branch = re.compile(
        r"ESPressio-Development-Platform/ESPressio-[A-Za-z0-9-]+\.git#"
        r"(?:main|structural_realignment(?:_[A-Za-z0-9-]+)*|work/[A-Za-z0-9_./-]+)"
    )
    for repository, relative in active:
        text = read(root, repository, relative, errors)
        if not text:
            continue
        if "primitives_redesign" not in text:
            fail(errors, f"ESPressio-{repository}/{relative}: canonical redesign branch is not documented")
        match = stale_branch.search(text)
        if match:
            fail(errors, f"ESPressio-{repository}/{relative}: stale active branch guidance {match.group(0)!r}")


def validate_web(root: Path, errors: list[str]) -> None:
    discovery_path = "src/ESPressio_WebPrimitiveDiscovery.hpp"
    discovery = read(root, "Web", discovery_path, errors)
    require(discovery, "Web", discovery_path,
            ("Primitive::TypeDirectoryView", "IsFrozen()", "PrimitiveTypeDiscovery"), errors)
    forbid(discovery, "Web", discovery_path,
           ("ESPressio_Command", "ESPressio_Event", "ESPressio_State", "CommandRegistry", "EventTransportManager"), errors)

    command_path = "src/ESPressio_WebCommand.hpp"
    command = read(root, "Web", command_path, errors)
    require(command, "Web", command_path,
            ("IHttpCommandAuthorizer", "Primitive::TypeDirectoryView", "RequestSchema",
             "MaximumPayloadBytes", "SubmitDynamicCommand", "CommandDynamicConstructionMode::RequesterRequired"), errors)
    forbid(command, "Web", command_path,
           ("InboundCommandEvent", "CommandRegistry", "EventTransportManager"), errors)

    event_path = "src/ESPressio_WebEvent.hpp"
    event = read(root, "Web", event_path, errors)
    require(event, "Web", event_path,
            ("IHttpEventAuthorizer", "Primitive::TypeDirectoryView", "DynamicallyConstructible",
             "MaximumPayloadBytes", "DispatchDynamicEvent"), errors)
    forbid(event, "Web", event_path,
           ("EventTransportManager", "CommandRegistry", "InboundCommandEvent"), errors)

    state_path = "src/ESPressio_WebState.hpp"
    state = read(root, "Web", state_path, errors)
    require(state, "Web", state_path,
            ("IHttpStateAuthorizer", "Primitive::TypeDirectoryView", "MaximumPayloadBytes",
             "ReadDynamicState", "HttpMethod::Get", "HttpMethod::Head"), errors)
    forbid(state, "Web", state_path,
           ("StateOwner<", "BindOwner<", "CommandRegistry", "EventTransportManager"), errors)

    for evidence in (
        "tests/test_primitive_discovery.cpp",
        "tests/test_primitive_schema.cpp",
        "tests/test_web_command.cpp",
        "tests/test_web_event.cpp",
        "tests/test_web_state.cpp",
        ".github/workflows/primitives-redesign-discovery.yml",
        ".github/workflows/primitives-redesign-schema.yml",
        ".github/workflows/primitives-redesign-command.yml",
        ".github/workflows/primitives-redesign-event.yml",
        ".github/workflows/primitives-redesign-state.yml",
    ):
        require_file(root, "Web", evidence, errors)


def validate_lua(root: Path, errors: list[str]) -> None:
    discovery_path = "src/ESPressio_LuaPrimitiveDiscovery.hpp"
    discovery = read(root, "Lua", discovery_path, errors)
    require(discovery, "Lua", discovery_path,
            ("Primitive::TypeDirectoryView", "IsFrozen()", "RegisterPrimitiveDiscovery"), errors)
    forbid(discovery, "Lua", discovery_path,
           ("#include <ESPressio_Command", "#include <ESPressio_Event", "#include <ESPressio_State",
            "CommandRegistry", "EventTransportManager"), errors)

    command_path = "src/ESPressio_LuaCommand.hpp"
    command = read(root, "Lua", command_path, errors)
    require(command, "Lua", command_path,
            ("ILuaCommandAuthorizer", "RequestSchema", "payload.size() <= maximum",
             "SubmitDynamicCommand", "CommandDynamicConstructionMode::RequesterRequired"), errors)
    forbid(command, "Lua", command_path, ("CommandRegistry", "InboundCommandEvent", "EventTransportManager"), errors)

    event_path = "src/ESPressio_LuaEvent.hpp"
    event = read(root, "Lua", event_path, errors)
    require(event, "Lua", event_path,
            ("ILuaEventAuthorizer", "DynamicallyConstructible", "payload.size() <= maximum", "DispatchDynamicEvent"), errors)
    forbid(event, "Lua", event_path, ("EventTransportManager", "CommandRegistry"), errors)

    state_path = "src/ESPressio_LuaState.hpp"
    state = read(root, "Lua", state_path, errors)
    require(state, "Lua", state_path,
            ("ILuaStateAuthorizer", "TMaximumPayloadBytes", "ReadDynamicState", "RegisterStateInspection"), errors)
    forbid(state, "Lua", state_path, ("StateOwner<", "BindOwner<", "CommandRegistry", "EventTransportManager"), errors)

    for evidence in (
        "tests/primitive_discovery_tests.cpp",
        "tests/command_admission_tests.cpp",
        "tests/event_dispatch_tests.cpp",
        "tests/state_inspection_tests.cpp",
        ".github/workflows/primitives-redesign-discovery.yml",
        ".github/workflows/primitives-redesign-command.yml",
        ".github/workflows/primitives-redesign-event.yml",
        ".github/workflows/primitives-redesign-state.yml",
    ):
        require_file(root, "Lua", evidence, errors)


def validate_serial(root: Path, errors: list[str]) -> None:
    command_path = "src/command-console/ESPressio_CommandConsole.hpp"
    command = read(root, "Serial", command_path, errors)
    require(command, "Serial", command_path,
            ("Primitive::TypeDirectoryView", "ICommandConsoleAuthorizer", "RequestSchema",
             "SubmitDynamicCommand"), errors)
    forbid(command, "Serial", command_path, ("CommandRegistry", "EventTransportManager", "InboundCommandEvent"), errors)

    event_path = "src/event-console/ESPressio_EventConsole.hpp"
    event = read(root, "Serial", event_path, errors)
    require(event, "Serial", event_path,
            ("Primitive::TypeDirectoryView", "IEventConsoleAuthorizer", "DispatchDynamicEvent"), errors)
    forbid(event, "Serial", event_path, ("EventTransportManager", "CommandRegistry"), errors)

    state_path = "src/state/ESPressio_StateMonitor.hpp"
    state = read(root, "Serial", state_path, errors)
    require(state, "Serial", state_path,
            ("Primitive::TypeDirectoryView", "IStateMonitorAuthorizer", "ReadDynamicState",
             "TMaximumPayloadBytes"), errors)
    forbid(state, "Serial", state_path, ("StateOwner<", "BindOwner<", "CommandRegistry", "EventTransportManager"), errors)

    for evidence in (
        "tests/test_command_console.cpp",
        "tests/test_event_console.cpp",
        "tests/test_primitive_family_tooling.cpp",
        ".github/workflows/primitives-redesign-family-tooling.yml",
        ".github/workflows/state-monitor.yml",
    ):
        require_file(root, "Serial", evidence, errors)


def validate_wifi(root: Path, errors: list[str]) -> None:
    worker_path = "src/ESPressio_WiFiWorker.hpp"
    worker = read(root, "WiFi", worker_path, errors)
    require(worker, "WiFi", worker_path,
            ("Threads::ThreadWith<Threads::Precision<8>>", "GetCapability<Threads::PrecisionTag>()", ".Bump()"), errors)
    forbid(worker, "WiFi", worker_path,
           ("PrecisionThread", "PrecisionEventThread", "EventThreadBase", "EventTransportManager", "CommandRegistry"), errors)


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []

    validate_active_docs(root, errors)
    validate_web(root, errors)
    validate_lua(root, errors)
    validate_serial(root, errors)
    validate_wifi(root, errors)

    if errors:
        print("Cross-tool Primitive redesign validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        "Cross-tool Primitive redesign validation passed: Web, Lua, Serial and WiFi use the final "
        "frozen discovery/family APIs, independent authorization, bounded dynamic inputs and "
        "owner-safe State inspection contracts."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
