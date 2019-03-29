#include <npe.h>
#include <typedefs.h>






#include <igl/ray_sphere_intersect.h>

const char* ds_ray_sphere_intersect = R"igl_Qu8mg5v7(

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

 Compute the intersection between a ray from O in direction D and a sphere
   centered at C with radius r
  
   Inputs:
     o  origin of ray
     d  direction of ray
     c  center of sphere
     r  radius of sphere
   Outputs:
     t0  parameterization of first hit (set only if exists) so that hit
      position = o + t0*d
     t1  parameterization of second hit (set only if exists)
     
   Returns the number of hits
)igl_Qu8mg5v7";

npe_function(ray_sphere_intersect)
npe_doc(ds_ray_sphere_intersect)

npe_arg(o, dense_f32, dense_f64)
npe_arg(d, dense_f32, dense_f64)
npe_arg(c, dense_f32, dense_f64)


npe_begin_code()

  r_type r;
  t_type & t0;
  t_type & t1;
  igl::ray_sphere_intersect(o, d, c, r, t0, t1);
  return std::make_tuple(npe::move(r), npe::move(t0), npe::move(t1));

npe_end_code()


