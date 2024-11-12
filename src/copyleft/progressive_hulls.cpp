#include "default_types.h"
#include <igl/copyleft/progressive_hulls.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // igl::decimate is a nightmare of poor templating. Suffer copies.
  auto progressive_hulls(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const int max_m)
  {
    Eigen::MatrixXd U;
    Eigen::MatrixXi G;
    Eigen::VectorXi J;
    igl::copyleft::progressive_hulls(V,F,max_m,U,G,J);
    return std::make_tuple(
      U.cast<Numeric>().eval(), // If Numeric==double will this incur a copy?
      G.cast<Integer>().eval(),
      J.cast<Integer>().eval());
  }
}
void bind_progressive_hulls(nb::module_ &m)
{
  m.def(
    "progressive_hulls",
    &pyigl::progressive_hulls,
    "V"_a, "F"_a, "max_m"_a=0,
    R"(Performs progressive hull simplification on a mesh, collapsing edges until a target number of faces is reached.

    @param[in] V  #V by dim list of vertex positions
    @param[in] F  #F by 3 list of face indices into V
    @param[in] max_m Target number of output faces
    @param[out] U Output vertex positions
    @param[out] G Output face indices into U
    @param[out] J Indices into F indicating the birth face for each face in G)");
}
