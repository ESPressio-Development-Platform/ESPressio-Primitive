#!/usr/bin/env python3
"""Tranche 11 V11-05: guard forbidden dependency directions and branch drift.

V11-04 proves the exact direct DAG where the architecture locks a complete set.
This companion guard covers architectural negative edges plus coordinated branch
references in build/package/workflow surfaces across the entire active redesign
graph.  Documentation prose is audited separately by V11-03/V11-18.
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPOSITORIES = (
    "Primitive", "System", "Serializable", "Persistence", "Task", "Timing",
    "Threads", "Event", "Command", "State", "Adapters", "Radio", "Mesh",
    "MeshAdapters", "RadioAdapters", "Sockets", "Serial", "WiFi", "ESP32",
    "Logging", "Security", "Units", "Observable", "Web", "Lua", "NRF24",
)

FORBIDDEN_DEPENDENCIES: dict[str, set[str]] = {
    "System": {"Persistence"},
    "Timing": {"Threads", "Event", "Command", "State"},
    "Threads": {"Event", "Command", "State"},
    "Command": {"Event"},
    "State": {"Event", "Command"},
    "Adapters": {"Radio", "Event", "Command", "State", "Mesh"},
    "Radio": {"Primitive", "Event", "Command", "State", "Mesh", "Adapters", "RadioAdapters"},
    "Mesh": {"Event", "Command", "State", "MeshAdapters", "RadioAdapters"},
}

CONFIG_NAMES = {
    "library.json", "library.properties", "platformio.ini", "CMakeLists.txt",
    "component.mk", "idf_component.yml", "pyproject.toml",
}
WORKFLOW_SUFFIXES = {".yml", ".yaml"}

ESPRESSIO_GIT_REF = re.compile(
    r"(?:https://github\.com/)?ESPressio-Development-Platform/"
    r"ESPressio-[A-Za-z0-9-]+\.git#([A-Za-z0-9_./-]+)"
)


def normalize(name: str) -> str:
    prefix = "ESPressio-"
    return name[len(prefix):] if name.startswith(prefix) else name


def manifest_dependencies(manifest: Path) -> set[str]:
    data = json.loads(manifest.read_text(encoding="utf-8"))
    raw = data.get("dependencies", [])
    if isinstance(raw, dict):
        values = raw.keys()
    elif isinstance(raw, list):
        values = (
            item.get("name", "") if isinstance(item, dict) else str(item)
            for item in raw
        )
    else:
        raise ValueError(f"unsupported dependencies value {type(raw).__name__}")
    return {normalize(value) for value in values if value}


def config_surface(path: Path, repo: Path) -> bool:
    rel = path.relative_to(repo)
    if path.name in CONFIG_NAMES:
        return True
    return bool(rel.parts and rel.parts[0] == ".github" and path.suffix.lower() in WORKFLOW_SUFFIXES)


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    checked_configs = 0

    for name in REPOSITORIES:
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue

        manifest = repo / "library.json"
        if manifest.exists():
            try:
                dependencies = manifest_dependencies(manifest)
            except Exception as exc:
                errors.append(f"{repo.name}/library.json: {exc}")
            else:
                forbidden = sorted(FORBIDDEN_DEPENDENCIES.get(name, set()) & dependencies)
                if forbidden:
                    errors.append(f"{repo.name}: forbidden direct dependency edge(s) {forbidden}")

        for path in repo.rglob("*"):
            if not path.is_file() or ".git" in path.parts or not config_surface(path, repo):
                continue
            checked_configs += 1
            try:
                text = path.read_text(encoding="utf-8")
            except UnicodeDecodeError:
                continue
            for match in ESPRESSIO_GIT_REF.finditer(text):
                branch = match.group(1)
                if branch != "primitives_redesign":
                    line = text.count("\n", 0, match.start()) + 1
                    errors.append(
                        f"{path.relative_to(root)}:{line}: coordinated ESPressio dependency "
                        f"references #{branch}, expected #primitives_redesign"
                    )

    if errors:
        print("V11-05 forbidden dependency/branch validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        f"V11-05 forbidden dependency/branch validation passed across {len(REPOSITORIES)} "
        f"repositories and {checked_configs} build/package/workflow surfaces."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
