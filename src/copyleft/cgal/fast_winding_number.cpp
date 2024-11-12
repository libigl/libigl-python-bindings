#include "default_types.h"
#include <igl/copyleft/cgal/fast_winding_number.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Overload with `expansion_order` and `beta`
  auto fast_winding_number(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const nb::DRef<const Eigen::MatrixXN> &Q,
    int expansion_order,
    double beta)
  {
    Eigen::VectorXd WN;
    igl::copyleft::cgal::fast_winding_number(P, N, Q, expansion_order, beta, WN);
    return WN;
  }
}

// Bind the wrapper to the Python module
void bind_fast_winding_number(nb::module_ &m)
{
  m.def(
    "fast_winding_number",
    &pyigl::fast_winding_number,
    "P"_a,
    "N"_a,
    "Q"_a,
    "expansion_order"_a = 2,
    "beta"_a = 2.0,
    R"(Evaluate the fast winding number for point data with adjustable accuracy.

    @param[in] P  #P by 3 list of point locations
    @param[in] N  #P by 3 list of point normals
    @param[in] Q  #Q by 3 list of query points for the winding number
    @param[in] expansion_order  Order of the Taylor expansion (0, 1, or 2)
    @param[in] beta  Barnes-Hut style accuracy parameter (recommended: 2)
    @return Vector of winding number values for each query point)");

}
