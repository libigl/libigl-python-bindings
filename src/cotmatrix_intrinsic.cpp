#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/cotmatrix_intrinsic.h>

const char *ds_cotmatrix_intrinsic = R"igl_Qu8mg5v7(

Constructs the cotangent stiffness matrix (discrete laplacian) for a given
   mesh with faces F and edge lengths l.

Parameters
----------

l  #F by 3 list of (half-)edge lengths
F  #F by 3 list of face indices into some (not necessarily
  determined/embedable) list of vertex positions V. It is assumed #V ==
  F.maxCoeff()+1

Returns
-------

L  #V by #V sparse Laplacian matrix

See also
--------


Notes
-----
See also: cotmatrix, intrinsic_delaunay_cotmatrix

Examples
--------

)igl_Qu8mg5v7";

npe_function(cotmatrix_intrinsic)
npe_doc(ds_cotmatrix_intrinsic)

npe_arg(l, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_rows_match(l, f, "l", "f");
  assert_cols_equals(l, 3, "l");
  assert_valid_tri_mesh_faces(f);

  Eigen::SparseMatrix<npe_Scalar_l> mat;
  igl::cotmatrix_intrinsic(l, f, mat);
  return npe::move(mat);

npe_end_code()


