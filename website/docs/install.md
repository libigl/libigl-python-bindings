# Installation

## From PyPI (recommended)

```bash
python -m pip install libigl
```

Pre-built wheels are published for Linux, macOS, and Windows across the actively
supported CPython versions, so no compiler is required.

## Importing

```python
import igl
```

Submodules are imported explicitly:

```python
import igl.predicates
import igl.copyleft.cgal
import igl.embree
```

## Building from source

Building from source requires a C++17 compiler and CMake. libigl and its
dependencies are fetched automatically by CMake.

```bash
git clone https://github.com/libigl/libigl-python-bindings.git
cd libigl-python-bindings
python -m pip install .
```

To build only a subset of the (heavier) optional modules, pass the corresponding
CMake options (`LIBIGL_COPYLEFT_CGAL`, `LIBIGL_COPYLEFT_TETGEN`,
`LIBIGL_RESTRICTED_TRIANGLE`, `LIBIGL_EMBREE`, `LIBIGL_SPECTRA`,
`LIBIGL_PREDICATES`, `LIBIGL_CYCODEBASE`).
