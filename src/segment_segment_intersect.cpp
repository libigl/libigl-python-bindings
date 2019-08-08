// TODO: __example
// error at line 33 and 41, saying cross is only for certain size matrices

#include <npe.h>
#include <typedefs.h>






#include <igl/segment_segment_intersect.h>

const char* ds_segments_intersect = R"igl_Qu8mg5v7(

Determine whether two line segments A,B intersect
    A: p + t*r :  t \in [0,1]
    B: q + u*s :  u \in [0,1]

Parameters
----------
p  3-vector origin of segment A
r  3-vector direction of segment A
q  3-vector origin of segment B
s  3-vector direction of segment B
eps precision


Returns
-------
t  scalar point of intersection along segment A, t \in [0,1]
u  scalar point of intersection along segment B, u \in [0,1]
Returns true if intersection


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(segments_intersect)
npe_doc(ds_segments_intersect)

npe_arg(p, dense_float, dense_double)
npe_arg(r, npe_matches(p))
npe_arg(q, npe_matches(p))
npe_arg(s, npe_matches(p))


npe_begin_code()
  // TODO: remove __copy
  Eigen::Vector3d p_copy = p.template cast<double>();
  Eigen::Vector3d r_copy = r.template cast<double>();
  Eigen::Vector3d q_copy = q.template cast<double>();
  Eigen::Vector3d s_copy = s.template cast<double>();

  double t;
  double u;
  double eps;
  bool is_intersect = igl::segment_segment_intersect(p_copy, r_copy, q_copy, s_copy, t, u, eps);
  return std::make_tuple(is_intersect, t, u, eps);

npe_end_code()


