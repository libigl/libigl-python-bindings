// TODO: Fix the npe_arg for igl::AABB and std::function

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
npe_arg(n, dense_float, dense_double)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_p> s;
  igl::ambient_occlusion(v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()



const char* ds_ambient_occlusion = R"igl_Qu8mg5v7(

Compute ambient occlusion per given point

Parameters
----------
shoot_ray  function handle that outputs hits of a given ray against a
  mesh (embedded in function handles as captured variable/data)
P  #P by 3 list of origin points
N  #P by 3 list of origin normals


Returns
-------
S  #P list of ambient occlusion values between 1 (fully occluded) and
  0 (not occluded)


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

npe_arg(shoot_ray, std::function<bool (const Eigen::Vector3f &, const Eigen::Vector3f &)> &)
npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_p> s;
  igl::ambient_occlusion(shoot_ray, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()


const char* ds_ambient_occlusion = R"igl_Qu8mg5v7(

Parameters
----------
AABB  axis-aligned bounding box hierarchy around (V,F)

Returns
-------


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

npe_arg(aabb, igl::AABB<DerivedV, DIM> &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_p> s;
  igl::ambient_occlusion(aabb, v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()


