#include <npe.h>
#include <typedefs.h>
#include <igl/polar_svd.h>

const char* ds_polar_svd = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Computes the polar decomposition (R,T) of a matrix A using SVD singular
   value decomposition
  
   Inputs:
     A  3 by 3 matrix to be decomposed
   Outputs:
     R  3 by 3 rotation matrix part of decomposition (**always rotataion**)
     T  3 by 3 stretch matrix part of decomposition
     U  3 by 3 left-singular vectors
     S  3 by 1 singular values
     V  3 by 3 right-singular vectors
  
  
)igl_Qu8mg5v7";

npe_function(polar_svd)
npe_doc(ds_polar_svd)

npe_arg(a, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  EigenDense<npe_Scalar_> u;
  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> v;
  igl::polar_svd(a, r, t, u, s, v);
  return std::make_tuple(npe::move(r), npe::move(t), npe::move(u), npe::move(s), npe::move(v));

npe_end_code()
#include <igl/polar_svd.h>

const char* ds_polar_svd = R"igl_Qu8mg5v7(
See polar_svd for the documentation.
)igl_Qu8mg5v7";

npe_function(polar_svd)
npe_doc(ds_polar_svd)

npe_arg(a, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::polar_svd(a, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


