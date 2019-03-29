#include <npe.h>
#include <typedefs.h>






#include <igl/ray_box_intersect.h>

const char* ds_ray_box_intersect = R"igl_Qu8mg5v7(

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

 Determine whether a ray origin+t*dir and box intersect within the ray's parameterized
   range (t0,t1)
  
   Inputs:
     source  3-vector origin of ray
     dir  3-vector direction of ray
     box  axis aligned box
     t0  hit only if hit.t less than t0
     t1  hit only if hit.t greater than t1
   Outputs:
     tmin  minimum of interval of overlap within [t0,t1]
     tmax  maximum of interval of overlap within [t0,t1]
   Returns true if hit
)igl_Qu8mg5v7";

npe_function(ray_box_intersect)
npe_doc(ds_ray_box_intersect)

npe_arg(source, dense_f32, dense_f64)
npe_arg(dir, dense_f32, dense_f64)
npe_arg(box, Eigen::AlignedBox<Scalar, 3> &)
npe_arg(t0, Scalar &)
npe_arg(t1, Scalar &)


npe_begin_code()

  Scalar & tmin;
  Scalar & tmax;
  igl::ray_box_intersect(source, dir, box, t0, t1, tmin, tmax);
  return std::make_tuple(npe::move(tmin), npe::move(tmax));

npe_end_code()


