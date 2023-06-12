#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/gaussian_curvature.h>

const char* ds_gaussian_curvature = R"igl_Qu8mg5v7(
Compute discrete local integral gaussian curvature (angle deficit, without
averaging by local area).

Parameters
----------
v : #v by 3 array of mesh vertex 3D positions
f : #f by 3 array of face (triangle) indices

Returns
-------
k : #v by 1 array of discrete gaussian curvature values

See also
--------
principal_curvature

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> k = gaussian_curvature(v, f)
)igl_Qu8mg5v7";

npe_function(gaussian_curvature)
npe_doc(ds_gaussian_curvature)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> k;
  igl::gaussian_curvature(v, f, k);
  return npe::move(k);

npe_end_code()


