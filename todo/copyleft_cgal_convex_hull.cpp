#include <npe.h>
#include <typedefs.h>
#include <igl/convex_hull.h>

const char* ds_convex_hull = R"igl_Qu8mg5v7(

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

 Given a set of points (V), compute the convex hull as a triangle mesh (W,G)
       
       Inputs:
         V  #V by 3 list of input points
       Outputs:
         W  #W by 3 list of convex hull points
         G  #G by 3 list of triangle indices into W
)igl_Qu8mg5v7";

npe_function(convex_hull)
npe_doc(ds_convex_hull)

npe_arg(v, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  EigenDense<npe_Scalar_> g;
  igl::  copyleft::  cgal::convex_hull(v, w, g);
  return std::make_tuple(npe::move(w), npe::move(g));

npe_end_code()
#include <igl/convex_hull.h>

const char* ds_convex_hull = R"igl_Qu8mg5v7(

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

 Given a set of points (V), compute the convex hull as a triangle mesh (F)
       over input vertex set (V)
       
       Inputs:
         V  #V by 3 list of input points
       Outputs:
         F  #F by 3 list of triangle indices into V
      
)igl_Qu8mg5v7";

npe_function(convex_hull)
npe_doc(ds_convex_hull)

npe_arg(v, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::convex_hull(v, f);
  return npe::move(f);

npe_end_code()


