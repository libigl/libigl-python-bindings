#include <npe.h>
#include <typedefs.h>






#include <igl/line_segment_in_rectangle.h>

const char* ds_line_segment_in_rectangle = R"igl_Qu8mg5v7(

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

 Determine whether a line segment overlaps with a rectangle.
  
   Inputs:
     s  source point of line segment
     d  dest point of line segment
     A  first corner of rectangle
     B  opposite corner of rectangle
   Returns true if line segment is at all inside rectangle
)igl_Qu8mg5v7";

npe_function(line_segment_in_rectangle)
npe_doc(ds_line_segment_in_rectangle)

npe_arg(s, Eigen::Vector2d &)
npe_arg(d, Eigen::Vector2d &)
npe_arg(a, Eigen::Vector2d &)
npe_arg(b, Eigen::Vector2d &)


npe_begin_code()

  igl::line_segment_in_rectangle(s, d, a, b);
  return ;

npe_end_code()


