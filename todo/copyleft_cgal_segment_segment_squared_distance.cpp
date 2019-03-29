#include <npe.h>
#include <typedefs.h>






#include <igl/segment_segment_squared_distance.h>

const char* ds_segment_segment_squared_distance = R"igl_Qu8mg5v7(

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

 Given two segments S1 and S2 find the points on each of closest
       approach and the squared distance thereof.
       
       Inputs:
         S1  first segment
         S2  second segment
       Outputs:
         P1  point on S1 closest to S2
         P2  point on S2 closest to S1
         d  distance betwee P1 and S2
       Returns true if the closest approach is unique.
)igl_Qu8mg5v7";

npe_function(segment_segment_squared_distance)
npe_doc(ds_segment_segment_squared_distance)

npe_arg(s1, CGAL::Segment_3<Kernel> &)
npe_arg(s2, CGAL::Segment_3<Kernel> &)


npe_begin_code()

  CGAL::Point_3<Kernel> & p1;
  CGAL::Point_3<Kernel> & p2;
  typename Kernel::FT & d;
  igl::  copyleft::  cgal::segment_segment_squared_distance(s1, s2, p1, p2, d);
  return std::make_tuple(npe::move(p1), npe::move(p2), npe::move(d));

npe_end_code()


