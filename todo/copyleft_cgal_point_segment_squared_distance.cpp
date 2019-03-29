#include <npe.h>
#include <typedefs.h>






#include <igl/point_segment_squared_distance.h>

const char* ds_point_segment_squared_distance = R"igl_Qu8mg5v7(

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

 Given a point P1 and segment S2 find the points on each of closest
       approach and the squared distance thereof.
       
       Inputs:
         P1  point
         S2  segment
       Outputs:
         P2  point on S2 closest to P1
         d  distance betwee P1 and S2
)igl_Qu8mg5v7";

npe_function(point_segment_squared_distance)
npe_doc(ds_point_segment_squared_distance)

npe_arg(p1, CGAL::Point_3<Kernel> &)
npe_arg(s2, CGAL::Segment_3<Kernel> &)


npe_begin_code()

  CGAL::Point_3<Kernel> & p2;
  typename Kernel::FT & d;
  igl::  copyleft::  cgal::point_segment_squared_distance(p1, s2, p2, d);
  return std::make_tuple(npe::move(p2), npe::move(d));

npe_end_code()


