#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/intrinsic_delaunay_cotmatrix.h>

const char *ds_intrinsic_delaunay_cotmatrix = R"igl_Qu8mg5v7(

INTRINSIC_DELAUNAY_COTMATRIX Computes the discrete cotangent Laplacian of a
mesh after converting it into its intrinsic Delaunay triangulation (see,
e.g., [Fisher et al. 2007].

Parameters
----------

V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh elements (triangles or tetrahedra)

Returns
-------

L  #V by #V cotangent matrix, each row i corresponding to V(i,:)
l_intrinsic  #F by 3 list of intrinsic edge-lengths used to compute L
F_intrinsic  #F by 3 list of intrinsic face indices used to compute L

See also
--------
intrinsic_delaunay_triangulation, cotmatrix, cotmatrix_intrinsic

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_cotmatrix)
npe_doc(ds_intrinsic_delaunay_cotmatrix)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  Eigen::SparseMatrix<npe_Scalar_v> l;
  EigenDense<npe_Scalar_v> l_intrinsic;
  EigenDense<npe_Scalar_f> f_intrinsic;
  igl::intrinsic_delaunay_cotmatrix(v, f, l, l_intrinsic, f_intrinsic);
  return std::make_tuple(npe::move(l), npe::move(l_intrinsic), npe::move(f_intrinsic));

npe_end_code()

