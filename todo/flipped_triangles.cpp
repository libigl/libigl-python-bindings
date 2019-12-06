#include <npe.h>
#include <typedefs.h>
#include <igl/flipped_triangles.h>

const char *ds_flipped_triangles = R"igl_Qu8mg5v7(
 Finds the ids of the flipped triangles of the mesh V,F in the UV mapping uv

Parameters
----------
  V  #V by 2 list of mesh vertex positions
  F  #F by 3 list of mesh faces (must be triangles)

Returns
-------
  X  #flipped list of containing the indices into F of the flipped triangles

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(flipped_triangles)
npe_doc(ds_flipped_triangles)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_2d_tri_mesh(v, f);
  EigenLikeDense<npe_Scalar_f> x;
  igl::flipped_triangles(v, f, x);
  return npe::move(x);

npe_end_code()
