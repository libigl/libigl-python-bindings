// TODO: __miss 4 functions

#include <common.h>
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

  assert_valid_23d_tri_mesh(v, f);
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd u;
  Eigen::MatrixXi g;
  Eigen::VectorXi j;
  Eigen::VectorXi i;
  bool reach = igl::decimate(v_copy, f_copy, max_m, u, g, j, i);
  EigenDenseF64 u_row_major = u;
  EigenDenseI64 g_row_major = g.template cast<typename EigenDenseI64::Scalar>();
  // FIXME: vector not allowing row major, but they should be essentially the same so i feel we can leave it as col major
  Eigen::Matrix<typename EigenDenseI64::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> j_row_major = j.template cast<typename EigenDenseI64::Scalar>();
  Eigen::Matrix<typename EigenDenseI64::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> i_row_major = i.template cast<typename EigenDenseI64::Scalar>();
  return std::make_tuple(reach, npe::move(u_row_major), npe::move(g_row_major), npe::move(j_row_major), npe::move(i_row_major));

npe_end_code()


