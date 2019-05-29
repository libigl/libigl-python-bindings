#include <npe.h>
#include <typedefs.h>
#include <igl/point_solid_signed_squared_distance.h>

const char* ds_point_solid_signed_squared_distance = R"igl_Qu8mg5v7(

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

 POINT_SOLID_SIGNED_SQUARED_DISTANCE Given a set of points (Q) and the
       boundary mesh (VB,FB) of a solid (as defined in [Zhou et al. 2016],
       determine the signed squared distance for each point q in Q so that d(q,B) is
       negative if inside and positive if outside.
      
       Inputs:
         Q  #Q by 3 list of query point positions
         VB  #VB by 3 list of mesh vertex positions of B
         FB  #FB by 3 list of mesh triangle indices into VB
       Outputs:
         D
)igl_Qu8mg5v7";

npe_function(point_solid_signed_squared_distance)
npe_doc(ds_point_solid_signed_squared_distance)

npe_arg(q, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::  copyleft::  cgal::point_solid_signed_squared_distance(q, vb, fb, d);
  return npe::move(d);

npe_end_code()


