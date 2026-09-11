"""Compile misuse must fail for the intended diagnostic; public headers stand alone."""
from pathlib import Path
import subprocess
import tempfile
root = Path(__file__).resolve().parents[1]
with tempfile.TemporaryDirectory() as directory:
    output = str(Path(directory) / "object.o")
    common = ["c++", "-std=c++17", "-Wall", "-Wextra", "-Werror", "-fno-rtti", "-fno-exceptions", "-I" + str(root / "src")]
    for name, expected in [("compile_fail_policy.cpp", "Primitive policy must"), ("compile_fail_type_id.cpp", "conversion")]:
        result = subprocess.run(common + ["-c", str(root / "tests" / name), "-o", output], capture_output=True, text=True)
        assert result.returncode != 0 and expected in result.stderr, result.stderr
    for header in sorted((root / "src").glob("*.hpp")):
        source = Path(directory) / "header.cpp"
        source.write_text('#include "' + header.name + '"\n')
        subprocess.run(common + ["-c", str(source), "-o", output], check=True)
print("Negative contracts and independent no-RTTI/no-exception headers passed")
