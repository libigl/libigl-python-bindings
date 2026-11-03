"""Generate stubs using the actual Wasm extensions, then update wheel RECORD."""

import argparse
import ast
import os
from pathlib import Path
import subprocess
import tempfile
from zipfile import ZipFile

from wheel.wheelfile import WheelFile


def repair(wheel: Path, destination: Path) -> None:
    wheel = wheel.resolve()
    destination.mkdir(parents=True, exist_ok=True)
    destination = destination.resolve()
    with tempfile.TemporaryDirectory(prefix="libigl-stubs-") as temporary:
        root = Path(temporary)
        unpacked = root / "wheel"
        with ZipFile(wheel) as archive:
            archive.extractall(unpacked)

        env = os.environ.copy()
        # Pyodide normally excludes /tmp from its host filesystem mounts.
        env["_PYODIDE_EXTRA_MOUNTS"] = os.pathsep.join(
            filter(None, [env.get("_PYODIDE_EXTRA_MOUNTS"), str(root)])
        )
        venv = root / "venv"
        subprocess.run(["pyodide", "venv", str(venv)], check=True, env=env)
        # Match the nanobind version used to compile the extensions in CMake.
        subprocess.run(
            [str(venv / "bin/pip"), "install", str(wheel), "nanobind==2.7.0"],
            check=True, env=env,
        )
        extensions = sorted((unpacked / "igl").rglob("*.so"))
        if not extensions:
            raise RuntimeError("No libigl extensions found in the Pyodide wheel")
        for extension in extensions:
            relative = extension.relative_to(unpacked)
            name = extension.name.split(".", 1)[0]
            module = ".".join((*relative.parent.parts, name))
            stub = extension.with_name(name + ".pyi")
            subprocess.run(
                [str(venv / "bin/python"), "-m", "nanobind.stubgen",
                 "-m", module, "-o", str(stub)],
                check=True, env=env, cwd=root,
            )
            ast.parse(stub.read_text(), filename=str(stub))

        # WheelFile recomputes hashes and sizes, including the newly added stubs.
        with WheelFile(str(destination / wheel.name), "w") as output:
            output.write_files(str(unpacked))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("wheel", type=Path)
    parser.add_argument("destination", type=Path)
    args = parser.parse_args()
    repair(args.wheel, args.destination)
