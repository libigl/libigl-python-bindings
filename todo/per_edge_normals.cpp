#include <npe.h>
#include <typedefs.h>
#include <igl/per_edge_normals.h>

const char* ds_per_edge_normals = R"igl_Qu8mg5v7(

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

 Compute face normals via vertex position list, face list
   Inputs:
     V  #V by 3 eigen Matrix of mesh vertex 3D positions
     F  #F by 3 eigen Matrix of face (triangle) indices
     weight  weighting type
     FN  #F by 3 matrix of 3D face normals per face
   Output:
     N  #2 by 3 matrix of mesh edge 3D normals per row
     E  #E by 2 matrix of edge indices per row
     EMAP  #E by 1 matrix of indices from all edges to E
  
)igl_Qu8mg5v7";

npe_function(per_edge_normals)
npe_doc(ds_per_edge_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(weight, igl::PerEdgeNormalsWeightingType)
npe_arg(fn, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  igl::per_edge_normals(v, f, weight, fn, n, e, emap);
  return std::make_tuple(npe::move(n), npe::move(e), npe::move(emap));

npe_end_code()
#include <igl/per_edge_normals.h>

const char* ds_per_edge_normals = R"igl_Qu8mg5v7(
See per_edge_normals for the documentation.
)igl_Qu8mg5v7";

npe_function(per_edge_normals)
npe_doc(ds_per_edge_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(weight, igl::PerEdgeNormalsWeightingType)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  igl::per_edge_normals(v, f, weight, n, e, emap);
  return std::make_tuple(npe::move(n), npe::move(e), npe::move(emap));

npe_end_code()
#include <igl/per_edge_normals.h>

const char* ds_per_edge_normals = R"igl_Qu8mg5v7(
See per_edge_normals for the documentation.
)igl_Qu8mg5v7";

npe_function(per_edge_normals)
npe_doc(ds_per_edge_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  igl::per_edge_normals(v, f, n, e, emap);
  return std::make_tuple(npe::move(n), npe::move(e), npe::move(emap));

npe_end_code()


