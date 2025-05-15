# libigl Python Bindings
[![PyPI version](https://badge.fury.io/py/libigl.svg)](https://pypi.org/project/libigl/)
[![buildwheels](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml/badge.svg)](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml?query=branch%3Amain)

This repository contains the source code for the python bindings for the C++
[libigl](https://github.com/libigl/libigl) library written using
[nanobind](https://nanobind.readthedocs.io/en/latest/). Functions allow NumPy
arrays as input and output for dense matrices and vectors and SciPy sparse
matrices for sparse matrices. 

## Installation

```
python -m pip install libigl
```

## Documentation

| :warning: WARNING           |
|:----------------------------|
| The [python-binding documentation](https://libigl.github.io/libigl-python-bindings/) is perennially out of date and will likely be removed/changed. |

* A tutorial on how to use the bindings can be found [here](https://libigl.github.io/libigl-python-bindings/tutorials/)
* A function reference can be found [here](https://libigl.github.io/libigl-python-bindings/igl_docs/)

## Getting the current version of libigl within python code

Since version 2.5.4.dev0, the `igl.__version__` attribute has been removed. To
get the version of the libigl package you're using within your python code, you
can use the following code:

```
import importlib.metadata
libigl_version = importlib.metadata.version('libigl')
```

The version of libigl is defined in the [pyproject.toml](./pyproject.toml) file.


## Compiling and modifying the bindiings

According to the [scikit-build-core documentation](https://scikit-build-core.readthedocs.io/en/latest/configuration.html#editable-installs), the way to make an editable (incremental) build is to:

 1. Preinstall the dependencies (at the top of pyproject.toml 
 2. Then use this very long command:

```
CMAKE_BUILD_PARALLEL_LEVEL=10  python -m pip install --no-build-isolation --config-settings=editable.rebuild=true -Cbuild-dir=build -ve.
```

The `CMAKE_BUILD_PARALLEL_LEVEL=10` will invoke with 10 parallel build threads.

### Adding a missing binding

Bindings are fairly mechanical to write. For example, suppose we didn't have a
binding for the c++ function `igl::moments`. The first step would be to look at
the corresponding `.h` header file in the C++ libigl library:
[moments.h](https://github.com/libigl/libigl/blob/main/include/igl/moments.h).

Then we would create the [src/moments.cpp](src/moments.cpp) file in this project
which uses `Eigen::MatrixXN` for numeric types and `Eigen::MatrixXI` for integer
types. Typically this requires a simple wrapper around the function matching
its signature to these types and some boilerplate `void bind_moments(...` code which adds the function to the python module.

Simply adding this `.cpp` file will be enough to add the bindings on the next
build.

If submitting a pull request with a new binding, please also add an execution
test in `tests/test_all.py` to ensure the binding can at least be called as
expected.


## Testing cibuildwheel locally

Install whichever version of Python from the [official website](https://www.python.org/downloads/) and then run:

    
    /Library/Frameworks/Python.framework/Versions/3.11/bin/python3.11 -m venv venv-official-3.11
    source venv-official-3.11/bin/activate
    python -m pip install cibuildwheel
    CIBW_BUILD="cp311-*" python -m cibuildwheel --output-dir wheelhouse --platform macos

## Downloading all the artifacts

A successful [.github/workflows/wheels.yml](.github/workflows/wheels.yml) run will a lot of `.whl` files. To download these all at once, you can use the following command:

    mkdir wheelhouse
    cd wheelhouse
    gh run download [runid]

Then these can be uploaded to pypi using:

    python -m twine upload --repository testpypi wheelhouse/*/*.whl wheelhouse/*/*.tar.gz

## Acknowledgements

The original python bindings were generated and maintained by
[@teseoch](https://github.com/teseoch),
[@KarlLeell](https://github.com/KarlLeell),
[@fwilliams](https://github.com/fwilliams),
[@skoch9](https://github.com/skoch9), and
[@danielepanozzo](https://github.com/danielepanozzo)

The modern python bindings (since 2.5.4.dev0) can largely be blamed on
[@alecjacobson](https://github.com/alecjacobson).
