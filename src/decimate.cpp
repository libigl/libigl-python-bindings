#include "default_types.h"
#include <igl/decimate.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // igl::decimate is a nightmare of poor templating. Suffer copies.
  auto decimate(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const int max_m,
    const bool block_intersections)
  {
    Eigen::MatrixXd U;
    Eigen::MatrixXi G;
    Eigen::VectorXi J,I;
    igl::decimate(V,F,max_m,block_intersections,U,G,J,I);
    return std::make_tuple(
      U.cast<Numeric>().eval(), // If Numeric==double will this incur a copy?
      G.cast<Integer>().eval(),
      J.cast<Integer>().eval(),
      I.cast<Integer>().eval());
  }
}

// Bind the wrapper to the Python module
void bind_decimate(nb::module_ &m)
{
  m.def(
    "decimate",
    &pyigl::decimate, 
    "V"_a, 
    "F"_a,
    "max_m"_a = 0,
    "block_intersections"_a = false,
    R"(Assumes (V,F) is a manifold mesh (possibly with boundary) collapses edges
until desired number of faces is achieved. This uses default edge cost and
merged vertex placement functions {edge length, edge midpoint}.

See \fileinfo for more details.

@param[in] V  #V by dim list of vertex positions
@param[in] F  #F by 3 list of face indices into V.
@param[in] max_m  desired number of output faces
@param[in] block_intersections  whether to block intersections (see
  intersection_blocking_collapse_edge_callbacks)
@param[out] U  #U by dim list of output vertex posistions (can be same ref as V)
@param[out] G  #G by 3 list of output face indices into U (can be same ref as G)
@param[out] J  #G list of indices into F of birth face
@param[out] I  #U list of indices into V of birth vertices
@return true if m was reached (otherwise #G > m))");

}




