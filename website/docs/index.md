# libigl Python bindings

[![PyPI version](https://badge.fury.io/py/libigl.svg)](https://pypi.org/project/libigl/)
[![build wheels](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml/badge.svg)](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml?query=branch%3Amain)

Python bindings for [libigl](https://libigl.github.io) — a simple C++ geometry
processing library. The bindings are NumPy-native: meshes are plain arrays
(`V` an `#V by 3` float array of vertices, `F` an `#F by 3` int array of faces),
and every function returns NumPy arrays or SciPy sparse matrices.

```bash
python -m pip install libigl
```

```python
import igl
import numpy as np

V, F = igl.read_triangle_mesh("bunny.obj")
L = igl.cotmatrix(V, F)                 # sparse cotangent Laplacian
N = igl.per_vertex_normals(V, F)        # per-vertex normals
K = igl.gaussian_curvature(V, F)        # discrete Gaussian curvature
```

## Where to go next

- **[API Reference](api/index.md)** — every bound function and class, grouped by
  module, generated directly from the installed package. Functions that also
  exist in C++ link straight to the [C++ Doxygen reference](https://libigl.github.io/dox/).
- **[Installation](install.md)** — pip, optional modules, and building from
  source.

## Modules

The core functionality lives in `igl`. Additional functionality that depends on
third-party libraries is grouped into submodules:

| Module | Contents |
| --- | --- |
| `igl` | core geometry processing (Laplacians, curvature, distances, parametrization, deformation, …) |
| `igl.predicates` | exact geometric predicates (orientation, incircle, winding numbers) |
| `igl.cycodebase` | cubic Bézier / spline distance and root-finding |
| `igl.copyleft`, `igl.copyleft.cgal`, `igl.copyleft.tetgen` | GPL-licensed functionality (booleans, meshing) |
| `igl.embree` | Embree-accelerated ray casting and ambient occlusion |
| `igl.triangle` | Triangle-based 2D meshing |
| `igl.spectra` | Spectra-based sparse eigensolves |

!!! note
    These bindings are under active development. If a function you need is
    missing, please [open an issue](https://github.com/libigl/libigl-python-bindings/issues).
