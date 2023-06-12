# Contributing


We are trying to keep the development of the bindings flexible, thus there is no much organization/maintenance.

If you want to contribute and expose additional features, thank you!

For any new binding please create a new pull request on git, if everything looks good we will merge it.

**Note 1**, see your new feature in the conda/pip version it might require some time, since we are planning to accumulate several fixes and
features before publishing a new version on conda/PPI.

The general rule of thumb is to keep the python side clean, and copy/hack in the binding if necessary.
In such a way, if something is fixed (on igl or the bindings) it will not break any python code.


## Binding a function

**Note** The following are rough instructions, proceed with caution!

1. Some function have already a binding skeleton, you can look in subfolders of `attic`. If the file exists move it to `src`, otherwise copy an existing binding.
2. Move to documentation in the correct spots.
3. Fix the input types:
    * every `MatrixXi` it should have `dense_int`, `dense_long`, `dense_longlong`
    * every `MatrixXd` it should be `dense_float`, `dense_double`
    * similar for sparse matrice
    * avoid having too many combinations, for instance the second `MatrixXi` should be `npe_matches(v)`
4. **IMPORTANT**: add assertions regarding the input (in particular the sizes), [common.h](https://github.com/libigl/libigl-python-bindings/blob/master/src/include/common.h) contains examples and typical assertions.
5. If libigl has overloading, you can either remove some functions (e.g, multiple return type can be skipped in ptyhon) or give them different names.
6. If libigl is not properly templated (or any other template related problem), you can create a copy of the input (see [qslim.cpp](https://github.com/libigl/libigl-python-bindings/blob/master/src/qslim.cpp)). In this case add the suffix `_copy` to any copied the variable and return the correct python type (which might involve another copy).
7. *Add a test* to just run the new function in the [test_basic.py](https://github.com/libigl/libigl-python-bindings/blob/master/tests/test_basic.py) file. At least assert for the correct `dtype`, `size`, and  `c_contiguous` (correct major).

A simple complete example is [decimate.cpp](https://github.com/libigl/libigl-python-bindings/blob/master/src/decimate.cpp).

Some times, libigl will not compile because of the MatrixBase vs PlainObjectBase, you need to change the PlainObjectBase to MatrixBase to make it compile.
This requires chaning libigl, so you need to create a PR in the main repository.


## Binding a class

We strongly discurage binding classes since it is more difficult and most of igl function do not require it.

If you still want to try, consider the option of "hidig the class in python", that is expose only the final compute, and internally  allocate the object, call the methods and then compute.

If you are still convinced that a class (more complicated) is the way to go look at [classes.cpp](https://github.com/libigl/libigl-python-bindings/blob/master/classes/classes.cpp) for an example. There are not many guidelines for that since most igl function are class-less.


In any case, **IMPORTANT**: add assertions regarding the input (in particular the sizes), [common.h](https://github.com/libigl/libigl-python-bindings/blob/master/src/include/common.h) contains examples and typical assertions.
