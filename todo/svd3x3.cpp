#include <npe.h>
#include <typedefs.h>






#include <igl/svd3x3.h>

const char* ds_svd3x3 = R"igl_Qu8mg5v7(

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

 Super fast 3x3 SVD according to http:pages.cs.wisc.edu/~sifakis/project_pages/svd.html
   The resulting decomposition is A = U * diag(S[0], S[1], S[2]) * V'
   BEWARE: this SVD algorithm guarantees that det(U) = det(V) = 1, but this 
   comes at the cost that 'sigma3' can be negative
   for computing polar decomposition it's great because all we need to do is U*V'
   and the result will automatically have positive determinant
  
   Inputs:
     A  3x3 matrix
   Outputs:
     U  3x3 left singular vectors
     S  3x1 singular values
     V  3x3 right singular vectors
  
   Known bugs: this will not work correctly for double precision.
)igl_Qu8mg5v7";

npe_function(svd3x3)
npe_doc(ds_svd3x3)

npe_arg(a, Eigen::Matrix<T, 3, 3> &)


npe_begin_code()

  Eigen::Matrix<T, 3, 3> & u;
  Eigen::Matrix<T, 3, 1> & s;
  Eigen::Matrix<T, 3, 3> & v;
  igl::svd3x3(a, u, s, v);
  return std::make_tuple(npe::move(u), npe::move(s), npe::move(v));

npe_end_code()


