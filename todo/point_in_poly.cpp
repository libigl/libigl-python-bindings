#include <npe.h>
#include <typedefs.h>






#include <igl/point_in_poly.h>

const char* ds_point_in_poly = R"igl_Qu8mg5v7(

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

 Determine if 2d point is inside a 2D polygon
   Inputs:
     poly  vector of polygon points, [0]=x, [1]=y. 
           Polyline need not be closed (i.e. first point != last point), 
           the line segment between last and first selected points is constructed 
           within this function.
     x     x-coordinate of query point
     y     y-coordinate of query point
   Returns true if query point is in polygon, false otherwise
   from http:www.visibone.com/inpoly/
)igl_Qu8mg5v7";

npe_function(point_in_poly)
npe_doc(ds_point_in_poly)

npe_arg(poly, std::vector<std::vector<unsigned int> > &)
npe_arg(xt, unsigned int)
npe_arg(yt, unsigned int)


npe_begin_code()

  igl::point_in_poly(poly, xt, yt);
  return ;

npe_end_code()


