# libigl Python Bindings
[![PyPI version](https://badge.fury.io/py/libigl.svg)](https://pypi.org/project/libigl/)
[![buildwheels](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml/badge.svg)](https://github.com/libigl/libigl-python-bindings/actions/workflows/wheels.yml?query=branch%3Amain)


This repository contains the source code for the libigl Python bindings. These bindings are fully compatible with NumPy and SciPy and offer a convenient interface similar to functions in those libraries.

These bindings are still under active development and should still be considered alpha quality. We encourage users to post issues so we can improve the bindings!

## Installation

```
python -m pip install libigl
```

If you wish to install the current development code, you can compile the library from scratch. Clone this repo and issue

```
python -m pip install ./
```


## [Help/Documentation](https://libigl.github.io/libigl-python-bindings/)

* A tutorial on how to use the bindings can be found [here](https://libigl.github.io/libigl-python-bindings/tutorials/)
* A function reference can be found [here](https://libigl.github.io/libigl-python-bindings/igl_docs/)

## Compiling and modifying the bindiings
After installing numpy & scipy and then cloning this repository, you can compile the bindings from scratch by running:

```
python setup.py develop
```

or

```
python setup.py build --debug develop
```

for debug compilation. This command will make the package `igl` available for import in the
current shell.

To run the tests:

```
python setup.py test
```

or

```
python tests/test_basic.py
```

and if developing and trying to run from this directory. You could use:

```
PYTHONPATH=. python tests/test_basic.py
```

