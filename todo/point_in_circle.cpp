#include <npe.h>
#include <typedefs.h>






#include <igl/point_in_circle.h>

const char* ds_point_in_circle = R"igl_Qu8mg5v7(

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

 Determine if 2d point is in a circle
   Inputs:
     qx  x-coordinate of query point
     qy  y-coordinate of query point
     cx  x-coordinate of circle center
     cy  y-coordinate of circle center
     r  radius of circle
   Returns true if query point is in circle, false otherwise
)igl_Qu8mg5v7";

npe_function(point_in_circle)
npe_doc(ds_point_in_circle)

npe_arg(qx, double)
npe_arg(qy, double)
npe_arg(cx, double)
npe_arg(cy, double)
npe_arg(r, double)


npe_begin_code()

  igl::point_in_circle(qx, qy, cx, cy, r);
  return ;

npe_end_code()


