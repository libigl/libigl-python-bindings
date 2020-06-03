#include <npe.h>
#include <typedefs.h>






#include <igl/point_triangle_squared_distance.h>

const char* ds_point_triangle_squared_distance = R"igl_Qu8mg5v7(

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

 Given a point P1 and triangle T2 find the points on each of closest
       approach and the squared distance thereof.
       
       Inputs:
         P1  point
         T2  triangle
       Outputs:
         P2  point on T2 closest to P1
         d  distance betwee P1 and T2
)igl_Qu8mg5v7";

npe_function(point_triangle_squared_distance)
npe_doc(ds_point_triangle_squared_distance)

npe_arg(p1, CGAL::Point_3<Kernel> &)
npe_arg(t2, CGAL::Triangle_3<Kernel> &)


npe_begin_code()

  CGAL::Point_3<Kernel> & p2;
  typename Kernel::FT & d;
  igl::  copyleft::  cgal::point_triangle_squared_distance(p1, t2, p2, d);
  return std::make_tuple(npe::move(p2), npe::move(d));

npe_end_code()


