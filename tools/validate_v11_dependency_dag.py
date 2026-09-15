#!/usr/bin/env python3
"""Tranche 11 V11-04: validate the locked final Primitive-platform dependency DAG.

The architecture handoff defines exact direct ESPressio dependency sets for the
redesigned core/family/adapter repositories below.  This gate treats package
manifests as executable architecture: missing manifests, missing edges and extra
edges are all failures.  Integration/tooling repositories whose complete direct
sets are not locked by this table remain covered by the separate V11-05
forbidden-edge/branch guard.
"""

from __future__ import annotations

import json
import sys
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
    "Command": {
        "System", "Primitive", "Task", "Threads", "Timing", "Serializable", "Persistence"
    },
    "State": {"System", "Primitive", "Threads", "Timing", "Serializable", "Persistence"},
    "Radio": {"System", "Task", "Timing", "Units"},
    "RadioAdapters": {"Radio", "Adapters", "Primitive", "Event", "Command", "State"},
    "Mesh": {"System", "Primitive", "Radio", "Timing", "Security", "Threads"},
    "MeshAdapters": {"Mesh", "Adapters", "Primitive", "Event", "Command", "State"},
    "Units": set(),
}


def normalize(name: str) -> str:
    prefix = "ESPressio-"
    return name[len(prefix):] if name.startswith(prefix) else name


def direct_dependencies(manifest: Path) -> set[str]:
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


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    errors: list[str] = []

    for name, expected in LOCKED_DAG.items():
        repo = root / f"ESPressio-{name}"
        manifest = repo / "library.json"
        if not repo.exists():
            errors.append(f"missing checked-out redesign repository: {repo.name}")
            continue
        if not manifest.exists():
            errors.append(f"{repo.name}: locked DAG repository has no library.json manifest")
            continue
        try:
            actual = direct_dependencies(manifest)
        except Exception as exc:
            errors.append(f"{repo.name}/library.json: {exc}")
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
                f"found {sorted(actual)} ({', '.join(details)})"
            )

    if errors:
        print("V11-04 exact dependency DAG validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    edge_count = sum(len(values) for values in LOCKED_DAG.values())
    print(
        f"V11-04 exact dependency DAG passed: {len(LOCKED_DAG)} locked repositories, "
        f"{edge_count} exact direct ESPressio edges."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
