#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/random_points_on_mesh_intrinsic.h>

const char* ds_random_points_on_mesh_intrinsic = R"igl_Qu8mg5v7(
RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.
Parameters
----------
     n  number of samples
     dblA  #F list of double areas of triangles

Returns
-------
     B  n by 3 list of barycentric coordinates, ith row are coordinates of
       ith sampled point in face FI(i)
     FI  n list of indices into F

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(random_points_on_mesh_intrinsic)
npe_doc(ds_random_points_on_mesh_intrinsic)

npe_arg(n, int)
npe_arg(dblA, dense_float, dense_double)


npe_begin_code()

  EigenDenseLike<npe_Matrix_dblA> b;
  EigenDenseInt fi;
  igl::random_points_on_mesh_intrinsic(n, dblA, b, fi);
  return std::make_tuple(npe::move(b), npe::move(fi));

npe_end_code()

