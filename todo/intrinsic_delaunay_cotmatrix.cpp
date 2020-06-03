#include <npe.h>
#include <typedefs.h>
#include <igl/intrinsic_delaunay_cotmatrix.h>

const char* ds_intrinsic_delaunay_cotmatrix = R"igl_Qu8mg5v7(

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

 INTRINSIC_DELAUNAY_COTMATRIX Computes the discrete cotangent Laplacian of a
   mesh after converting it into its intrinsic Delaunay triangulation (see,
   e.g., [Fisher et al. 2007].
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh elements (triangles or tetrahedra)
   Outputs: 
     L  #V by #V cotangent matrix, each row i corresponding to V(i,:)
     l_intrinsic  #F by 3 list of intrinsic edge-lengths used to compute L
     F_intrinsic  #F by 3 list of intrinsic face indices used to compute L
  
   See also: intrinsic_delaunay_triangulation, cotmatrix, cotmatrix_intrinsic
)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_cotmatrix)
npe_doc(ds_intrinsic_delaunay_cotmatrix)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Sparse_f64 l;
  EigenDense<npe_Scalar_> l_intrinsic;
  EigenDense<npe_Scalar_> f_intrinsic;
  igl::intrinsic_delaunay_cotmatrix(v, f, l, l_intrinsic, f_intrinsic);
  return std::make_tuple(npe::move(l), npe::move(l_intrinsic), npe::move(f_intrinsic));

npe_end_code()
#include <igl/intrinsic_delaunay_cotmatrix.h>

const char* ds_intrinsic_delaunay_cotmatrix = R"igl_Qu8mg5v7(
See intrinsic_delaunay_cotmatrix for the documentation.
)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_cotmatrix)
npe_doc(ds_intrinsic_delaunay_cotmatrix)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Sparse_f64 l;
  igl::intrinsic_delaunay_cotmatrix(v, f, l);
  return npe::move(l);

npe_end_code()


