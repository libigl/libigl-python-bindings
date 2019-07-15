// TODO: __missing miss the rest two functions with AABB and shoot_ray. __example

#include <npe.h>
#include <typedefs.h>
#include <igl/ambient_occlusion.h>

const char* ds_ambient_occlusion = R"igl_Qu8mg5v7(

Parameters
----------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of mesh face indices into V
P  #P by 3 list of origin points
N  #P by 3 list of origin normals

Returns
-------
S  #P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(ambient_occlusion)
npe_doc(ds_ambient_occlusion)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)
npe_arg(n, npe_matches(p))
npe_arg(num_samples, int)


npe_begin_code()

  npe_Matrix_p s;
  igl::ambient_occlusion(v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()
