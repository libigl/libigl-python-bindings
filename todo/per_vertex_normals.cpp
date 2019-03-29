#include <npe.h>
#include <typedefs.h>
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(

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

 Compute vertex normals via vertex position list, face list
   Inputs:
     V  #V by 3 eigen Matrix of mesh vertex 3D positions
     F  #F by 3 eigne Matrix of face (triangle) indices
     weighting  Weighting type
   Output:
     N  #V by 3 eigen Matrix of mesh vertex 3D normals
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(weighting, igl::PerVertexNormalsWeightingType)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_vertex_normals(v, f, weighting, n);
  return npe::move(n);

npe_end_code()
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(

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

 Without weighting
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_vertex_normals(v, f, n);
  return npe::move(n);

npe_end_code()
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(

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

 Inputs:
     FN  #F by 3 matrix of face (triangle) normals
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(weighting, igl::PerVertexNormalsWeightingType)
npe_arg(fn, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_vertex_normals(v, f, weighting, fn, n);
  return npe::move(n);

npe_end_code()
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(

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

 Without weighting
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(fn, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_vertex_normals(v, f, fn, n);
  return npe::move(n);

npe_end_code()


