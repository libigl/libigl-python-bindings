#include <npe.h>
#include <typedefs.h>
#include <common.h>
#include <igl/hessian.h>

const char *ds_hessian = R"igl_Qu8mg5v7(
 Constructs the finite element Hessian matrix
     as described in https:arxiv.org/abs/1707.04348,
     Natural Boundary Conditions for Smoothing in Geometry Processing
     (Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)
     The interior vertices are NOT set to zero yet.

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh faces (must be triangles)

Returns
-------
H  #V by #V Hessian energy matrix, each column i corresponding to V(i,:)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(hessian)
npe_doc(ds_hessian)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);
  EigenSparseLike<npe_Matrix_v> h;
  igl::hessian(v, f, h);
  return npe::move(h);
npe_end_code()


