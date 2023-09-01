igl python bindings
===================

[![PyPI version](https://badge.fury.io/py/libigl.svg)](https://pypi.org/project/libigl/)
[![buildwheels](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml/badge.svg)](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml?query=branch%3Amain)


!!! warning
    The igl python binding are in development, consider this a **beta** version.

[libigl](https://libigl.github.io) is a simple C++ geometry processing library. We have a wide functionality including construction of sparse discrete differential geometry operators and finite-elements matrices such as the cotangent Laplacian and diagonalized mass matrix, simple facet, and edge-based topology data structures.

All these functionalities are now available through python and can be easily installed with pip:
```bash
python -m pip install libigl
```

We provide a complete jupyter version of the tutorials and the full [documentation](igl_docs.md).

The full tutorial can be interactively run through mybinder
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/libigl/libigl-python-bindings/master?filepath=tutorial%2Ftutorials.ipynb)
