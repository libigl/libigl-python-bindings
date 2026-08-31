#include "default_types.h"
#include <igl/quad_planarity.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto quad_planarity(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXN P;
    igl::quad_planarity(V, F, P);
    return P;
  }
}

void bind_quad_planarity(nb::module_ &m)
{
  m.def(
    "quad_planarity",
    &pyigl::quad_planarity,
    "V"_a,
    "F"_a,
R"(Compute a planarity value for each quad in a quad mesh. Planarity is the
distance between the two diagonals of the quad divided by the average of the
diagonals' lengths (0 for a perfectly planar quad).

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 4 list of quad face indices into rows of V
@param[out] P  #F list of planarity values)");
}
