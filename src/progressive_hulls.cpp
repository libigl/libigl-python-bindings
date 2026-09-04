#include "default_types.h"
#include <igl/progressive_hulls.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto progressive_hulls(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const size_t max_m,
    const bool block_intersections)
  {
    // igl::progressive_hulls takes concrete Eigen::MatrixXd / int32 MatrixXi.
    const Eigen::MatrixXd Vd = V;
    const Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXd U;
    Eigen::MatrixXi G;
    Eigen::VectorXi J;
    const bool success =
      igl::progressive_hulls(Vd, Fi, max_m, block_intersections, U, G, J);
    return std::make_tuple(
      success,
      Eigen::MatrixXN(U),
      Eigen::MatrixXI(G.cast<Integer>()),
      Eigen::VectorXI(J.cast<Integer>()));
  }
}

void bind_progressive_hulls(nb::module_ &m)
{
  m.def(
    "progressive_hulls",
    &pyigl::progressive_hulls,
    "V"_a,
    "F"_a,
    "max_m"_a,
    "block_intersections"_a = false,
R"(Collapse edges until the desired number of faces is achieved, placing each new
vertex outside all previous meshes ("progressive hulls" from Sander et al.,
"Silhouette clipping" 2000). The result is a nested, enclosing coarsening of the
input.

Assumes (V,F) is a closed manifold mesh.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@param[in] max_m  desired number of output faces
@param[in] block_intersections  whether to refuse collapses that would introduce
    self-intersections
@param[out] success  true if max_m was reached (otherwise #G > max_m)
@param[out] U  #U by 3 list of output vertex positions
@param[out] G  #G by 3 list of output triangle indices into U
@param[out] J  #G list of indices into F of birth faces)");
}
