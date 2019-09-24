[![Build Status](https://travis-ci.com/geometryprocessing/libigl-python-bindings.svg?branch=master)](https://travis-ci.com/geometryprocessing/libigl-python-bindings)
[![Build status](https://ci.appveyor.com/api/projects/status/gti6d6encnc6akvr?svg=true)](https://ci.appveyor.com/project/teseoch/libigl-python-bindings)

## Installation

### With Conda [Recommended]
The simplest and best way to install the new LibIGL Python bindings is to run:
```
conda install -c conda-forge igl
```

### Compile from scratch [Not recommended]
If you wish to install the current master branch, you can compile the library from scratch, you can clone this repository and run the following command from the main directory:
```
python setup.py install
```

**NOTE:** We will not provide support for installations done in this way, since there is a lot of variation between systems. For a consistent experience. Use conda.

## Help/Documentation
The temporary documentation and tutorial can be found [here](https://geometryprocessing.github.io/libigl-python-bindings/tutorials/)

## Compiling and modifying the bindiings
After cloning this repository, you can compile the bindings from scratch by running:
```
python setup.py develop
```

The above command will make the package `igl` available for import in the current shell.

To run the tests:
```
python setup.py test
```



