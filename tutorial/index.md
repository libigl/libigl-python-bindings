igl python bindings
===================

[![Anaconda-Server Badge](https://anaconda.org/conda-forge/igl/badges/installer/conda.svg)](https://conda.anaconda.org/conda-forge)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/igl/badges/downloads.svg)](https://anaconda.org/conda-forge/igl)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/igl/badges/platforms.svg)](https://anaconda.org/conda-forge/igl)


!!! warning
    The igl python binding are in development, consider this a **beta** version.

[libigl](https://libigl.github.io) is a simple C++ geometry processing library. We have a wide functionality including construction of sparse discrete differential geometry operators and finite-elements matrices such as the cotangent Laplacian and diagonalized mass matrix, simple facet, and edge-based topology data structures.

All these functionalities are now available trough python and can be easily installed with conda:
```bash
conda install -c conda-forge igl
```

We provide a complete jupyter version of the [tutorial](tutorials.ipynb) and the full [documentation](igl_docs.md).

The full tutorial can be interactively run trough mybinder
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/libigl/libigl-python-bindings/master?filepath=tutorial%2Ftutorials.ipynb)