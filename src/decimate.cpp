// TODO: __miss 4 functions

#include <npe.h>
#include <typedefs.h>






#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges
  until desired number of faces is achieved. This uses default edge cost and
  merged vertex placement functions {edge length, edge midpoint}.

Parameters
----------
V  #V by dim list of vertex positions
F  #F by 3 list of face indices into V.
max_m  desired number of output faces

Returns
-------
U  #U by dim list of output vertex posistions (can be same ref as V)
G  #G by 3 list of output face indices into U (can be same ref as G)
J  #G list of indices into F of birth face
I  #U list of indices into V of birth vertices
Returns true if m was reached (otherwise #G > m)

See also
--------

Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(max_m, size_t)


npe_begin_code()

  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd u;
  Eigen::MatrixXi g;
  Eigen::VectorXi j;
  Eigen::VectorXi i;
  bool reach = igl::decimate(v_copy, f_copy, max_m, u, g, j, i);
  return std::make_tuple(reach, npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()


