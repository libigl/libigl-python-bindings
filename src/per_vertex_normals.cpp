#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(
Compute vertex normals via vertex position list, face list.

Parameters
----------
v : #v by 3 array of mesh vertex 3D positions
f : #f by 3 array of face (triangle) indices
weighting : Weighting type, one of the following
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted

Returns
-------
n  #v by 3 array of mesh vertex 3D normals

See also
--------
per_face_normals, per_edge_normals

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> n = per_vertex_normals(v, f)
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_longlong)
npe_default_arg(weighting, int, 0)

npe_begin_code()

  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM) == 0, "PerVertexNormalWeightingType enum changed!");
  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA) == 1, "PerVertexNormalWeightingType enum changed!");
  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE) == 2, "PerVertexNormalWeightingType enum changed!");

  EigenDenseLike<npe_Matrix_v> n;
  igl::per_vertex_normals(v, f, igl::PerVertexNormalsWeightingType(weighting), n);
  return npe::move(n);

npe_end_code()


