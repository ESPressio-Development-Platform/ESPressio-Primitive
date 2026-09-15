#!/usr/bin/env python3
"""V11-07: compile host-capable architectural public umbrellas without RTTI/exceptions.

Hardware/tooling target-only surfaces are intentionally deferred to V11-15. This proof
covers the platform architecture libraries whose public contracts are expected to be
host-parseable and independently includable on the final primitives_redesign graph.
"""
from __future__ import annotations

import subprocess
import sys
import tempfile
from pathlib import Path

HOST_UMBRELLAS: dict[str, str] = {
    "Primitive": "ESPressio_Primitive.hpp",
    "System": "ESPressio_System.hpp",
    "Serializable": "ESPressio_Serializable.hpp",
    "Persistence": "ESPressio_Persistence.hpp",
    "Task": "ESPressio_Task.hpp",
    "Timing": "ESPressio_Timing.hpp",
    "Threads": "ESPressio_Threads.hpp",
    "Event": "ESPressio_Event.hpp",
    "Command": "ESPressio_Command.hpp",
    "State": "ESPressio_State.hpp",
    "Adapters": "ESPressio_Adapters.hpp",
    "Radio": "ESPressio_Radio.hpp",
    "Mesh": "ESPressio_Mesh.hpp",
    "MeshAdapters": "ESPressio_MeshAdapters.hpp",
    "RadioAdapters": "ESPressio_RadioAdapters.hpp",
    "Units": "ESPressio_Units.hpp",
    "Observable": "ESPressio_Observable.hpp",
}


def main() -> int:
    root = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
    compiler = "c++"

    include_dirs: list[Path] = []
    for repo in sorted(root.glob("ESPressio-*")):
        source = repo / "src"
        if source.is_dir():
            include_dirs.append(source)

    timing_stubs = root / "ESPressio-Timing" / "tests" / "stubs"
    task_tests = root / "ESPressio-Task" / "tests"
    if timing_stubs.is_dir():
        include_dirs.append(timing_stubs)
    if task_tests.is_dir():
        include_dirs.append(task_tests)

    errors: list[str] = []
    compiled = 0
    with tempfile.TemporaryDirectory(prefix="espressio-v11-host-") as temp_dir:
        temp = Path(temp_dir)
        for repo_name, header in HOST_UMBRELLAS.items():
            header_path = root / f"ESPressio-{repo_name}" / "src" / header
            if not header_path.is_file():
                errors.append(f"ESPressio-{repo_name}: missing expected public umbrella {header}")
                continue

            source = temp / f"{repo_name}.cpp"
            source.write_text(f"#include <{header}>\nint main() {{ return 0; }}\n", encoding="utf-8")
            command = [
                compiler,
                "-std=c++17",
                "-Wall",
                "-Wextra",
                "-Werror",
                "-fno-rtti",
                "-fno-exceptions",
                "-fsyntax-only",
                str(source),
            ]
            for include_dir in include_dirs:
                command.extend(["-I", str(include_dir)])

            result = subprocess.run(command, text=True, capture_output=True)
            if result.returncode != 0:
                details = (result.stdout + result.stderr).strip()
                errors.append(f"ESPressio-{repo_name}/{header} failed restricted host compile:\n{details}")
            else:
                compiled += 1

    if errors:
        print("V11-07 restricted host public-header validation FAILED:", file=sys.stderr)
        for error in errors:
            print(f" - {error}", file=sys.stderr)
        return 1

    print(
        f"V11-07 restricted host public-header validation passed: {compiled} independent umbrellas, "
        "C++17/-Wall/-Wextra/-Werror/-fno-rtti/-fno-exceptions."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
