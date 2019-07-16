// error: static assertion failed: THIS_COEFFICIENT_ACCESSOR_TAKING_ONE_ACCESS_IS_ONLY_FOR_EXPRESSIONS_ALLOWING_LINEAR_ACCESS

#include <npe.h>
#include <typedefs.h>
#include <igl/unproject_ray.h>

const char* ds_unproject_ray = R"igl_Qu8mg5v7(

Construct a ray (source point + direction vector) given a screen space
  positions (e.g. mouse) and a model-view projection constellation.

Parameters
----------
pos  2d screen-space position (x,y) 
model  4x4 model-view matrix
proj  4x4 projection matrix
viewport  4-long viewport vector

Returns
-------
s  source of ray (pos unprojected with z=0)
dir  direction of ray (d - s) where d is pos unprojected with z=1


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unproject_ray)
npe_doc(ds_unproject_ray)

npe_arg(pos, dense_float, dense_double)
npe_arg(model, npe_matches(pos))
npe_arg(proj, npe_matches(pos))
npe_arg(viewport, npe_matches(pos))


npe_begin_code()

  npe_Matrix_pos s;
  npe_Matrix_pos dir;
  igl::unproject_ray(pos, model, proj, viewport, s, dir);
  return std::make_tuple(npe::move(s), npe::move(dir));

npe_end_code()


