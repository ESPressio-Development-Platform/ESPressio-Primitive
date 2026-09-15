#!/usr/bin/env python3
"""Tranche 11 V11-04: validate the locked final Primitive-platform dependency DAG.

Package manifests are authoritative where they exist. Header-only/interface adapter
repositories that deliberately have no package manifest are validated from direct
public-source includes resolved against uniquely-owned headers in the checked-out
redesign graph. This avoids inventing packaging metadata merely to represent a locked
architectural edge.
"""
from __future__ import annotations

import json
import re
import sys
from collections import defaultdict
from pathlib import Path

LOCKED_DAG: dict[str, set[str]] = {
    "Primitive": set(),
    "System": set(),
    "Serializable": {"System"},
    "Task": {"System"},
    "Timing": {"System", "Units", "Observable"},
    "Persistence": {"System", "Serializable", "Security"},
    "Threads": {"System", "Task", "Timing", "Units", "Observable"},
    "Adapters": {"System", "Primitive", "Task"},
    "Event": {"System", "Primitive", "Task", "Threads", "Timing", "Serializable"},
    "Command": {"System", "Primitive", "Task", "Threads", "Timing", "Serializable", "Persistence"},
    "State": {"System", "Primitive", "Threads", "Timing", "Serializable", "Persistence"},
    "Radio": {"System", "Task", "Timing", "Units"},
    "RadioAdapters": {"Radio", "Adapters", "Primitive", "Event", "Command", "State"},
    "Mesh": {"System", "Primitive", "Radio", "Timing", "Security", "Threads"},
    "MeshAdapters": {"Mesh", "Adapters", "Primitive", "Event", "Command", "State"},
    "Units": set(),
}

HEADER_SUFFIXES = {".h", ".hh", ".hpp", ".hxx"}
SOURCE_SUFFIXES = HEADER_SUFFIXES | {".c", ".cc", ".cpp", ".cxx", ".ino", ".ipp", ".tpp"}
INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', re.MULTILINE)


def normalize(name: str) -> str:
    prefix = "ESPressio-"
    return name[len(prefix):] if name.startswith(prefix) else name


def manifest_dependencies(manifest: Path) -> set[str]:
    data = json.loads(manifest.read_text(encoding="utf-8"))
    raw = data.get("dependencies", [])
    if isinstance(raw, dict):
        values = raw.keys()
    elif isinstance(raw, list):
        values = (item.get("name", "") if isinstance(item, dict) else str(item) for item in raw)
    else:
        raise ValueError(f"unsupported dependencies value {type(raw).__name__}")
    return {normalize(value) for value in values if value}


def build_header_index(root: Path) -> dict[str, set[str]]:
    owners: dict[str, set[str]] = defaultdict(set)
    for repo in root.glob("ESPressio-*"):
        if not repo.is_dir():
            continue
        source = repo / "src"
        if not source.exists():
            continue
        owner = normalize(repo.name)
        for path in source.rglob("*"):
            if path.is_file() and path.suffix.lower() in HEADER_SUFFIXES:
                owners[path.name].add(owner)
    return owners


def include_dependencies(repo: Path, owners: dict[str, set[str]]) -> set[str]:
    current = normalize(repo.name)
    dependencies: set[str] = set()
    source = repo / "src"
    if not source.exists():
        return dependencies
    for path in source.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in SOURCE_SUFFIXES:
            continue
        try:
            text = path.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            continue
        for match in INCLUDE.finditer(text):
            header = Path(match.group(1)).name
            candidates = owners.get(header, set())
            if len(candidates) != 1:
                continue
            owner = next(iter(candidates))
            if owner != current:
                dependencies.add(owner)
    return dependencies


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []
    owners = build_header_index(root)
    manifest_backed = 0
    include_backed = 0

    for name, expected in LOCKED_DAG.items():
        repo = root / f"ESPressio-{name}"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue
        manifest = repo / "library.json"
        try:
            if manifest.exists():
                actual = manifest_dependencies(manifest)
                evidence = "library.json"
                manifest_backed += 1
            else:
                actual = include_dependencies(repo, owners)
                evidence = "direct public includes"
                include_backed += 1
        except Exception as exc:
            errors.append(f"{repo.name}: dependency resolution failed: {exc}")
            continue

        if actual != expected:
            missing = sorted(expected - actual)
            extra = sorted(actual - expected)
            details: list[str] = []
            if missing:
                details.append(f"missing={missing}")
            if extra:
                details.append(f"extra={extra}")
            errors.append(
                f"{repo.name}: expected direct ESPressio dependencies {sorted(expected)}, "
                f"found {sorted(actual)} via {evidence} ({', '.join(details)})"
            )

    if errors:
        print("V11-04 exact dependency DAG validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    edge_count = sum(len(values) for values in LOCKED_DAG.values())
    print(
        f"V11-04 exact dependency DAG passed: {len(LOCKED_DAG)} locked repositories, "
        f"{edge_count} exact direct ESPressio edges; {manifest_backed} manifest-backed, "
        f"{include_backed} public-include-backed."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
