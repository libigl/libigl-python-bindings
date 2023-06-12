#include <npe.h>
#include <typedefs.h>

#include <igl/copyleft/cgal/convex_hull.h>

const char* ds_convex_hull = R"igl_Qu8mg5v7(
Given a set of points (V), compute the convex hull as a triangle mesh (F)
       
Parameters
----------
V :  #V by 3 list of input points

Returns
-------
F  #F by 3 list of triangle indices into V
)igl_Qu8mg5v7";

npe_function(convex_hull)
npe_doc(ds_convex_hull)

npe_arg(v, dense_float, dense_double)
npe_begin_code()

  EigenDenseInt g;
  igl::copyleft::cgal::convex_hull(v, g);
  return npe::move(g);

npe_end_code()
