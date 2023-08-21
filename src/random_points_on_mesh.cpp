//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/random_points_on_mesh.h>

const char* ds_random_points_on_mesh = R"igl_Qu8mg5v7(
RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.
Parameters
----------
     n  number of samples
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh triangle indices

Returns
-------
     B  n by 3 list of barycentric coordinates, ith row are coordinates of
       ith sampled point in face FI(i)
     FI  n list of indices into F
     X  n by dim list of sampled points

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(random_points_on_mesh)
npe_doc(ds_random_points_on_mesh)

npe_arg(n, int)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> b;
  EigenDenseLike<npe_Matrix_f> fi;
  EigenDenseLike<npe_Matrix_v> x;
  igl::random_points_on_mesh(n, v, f, b, fi, x);
  return std::make_tuple(npe::move(b), npe::move(fi), npe::move(x));

npe_end_code()
