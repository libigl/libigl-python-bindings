#include <npe.h>
#include <typedefs.h>






#include <igl/segments_intersect.h>

const char* ds_segments_intersect = R"igl_Qu8mg5v7(

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

 Determine whether two line segments A,B intersect
     A: p + t*r :  t \in [0,1]
     B: q + u*s :  u \in [0,1]
     Inputs:
       p  3-vector origin of segment A
       r  3-vector direction of segment A
       q  3-vector origin of segment B
       s  3-vector direction of segment B
      eps precision
     Outputs:
       t  scalar point of intersection along segment A, t \in [0,1]
       u  scalar point of intersection along segment B, u \in [0,1]
     Returns true if intersection
)igl_Qu8mg5v7";

npe_function(segments_intersect)
npe_doc(ds_segments_intersect)

npe_arg(p, dense_f32, dense_f64)
npe_arg(r, dense_f32, dense_f64)
npe_arg(q, dense_f32, dense_f64)
npe_arg(s, dense_f32, dense_f64)


npe_begin_code()

  double & t;
  double & u;
  double eps;
  igl::segments_intersect(p, r, q, s, t, u, eps);
  return std::make_tuple(npe::move(t), npe::move(u), npe::move(eps));

npe_end_code()


