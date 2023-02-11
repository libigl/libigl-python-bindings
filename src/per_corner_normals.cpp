#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/per_corner_normals.h>

const char *ds_per_corner_normals = R"igl_Qu8mg5v7(

Compute vertex normals via vertex position list, face list

Parameters
----------
V  #V by 3 eigen Matrix of mesh vertex 3D positions
F  #F by 3 eigen Matrix of face (triangle) indices
corner_threshold  threshold in degrees on sharp angles

Returns
-------
CN  #F*3 by 3 eigen Matrix of mesh vertex 3D normals, where the normal for corner F(i,j) is at CN(i*3+j,:)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(per_corner_normals)
npe_doc(ds_per_corner_normals)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(corner_threshold, double)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> n;
  igl::per_corner_normals(v, f, corner_threshold, n);
  return npe::move(n);

npe_end_code()

