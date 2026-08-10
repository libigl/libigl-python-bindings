#include "default_types.h"
#include <igl/cubic_is_flat.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool cubic_is_flat(
    const nb::DRef<const Eigen::MatrixXN> &C,
    const Numeric squared_distance_bound)
  {
    return igl::cubic_is_flat(C, squared_distance_bound);
  }
}

void bind_cubic_is_flat(nb::module_ &m)
{
  m.def("cubic_is_flat", &pyigl::cubic_is_flat, "C"_a, "squared_distance_bound"_a,
    R"(Test whether a cubic Bézier curve is flat within a given tolerance.

"Piecewise Linear Approximation of Bézier Curves" [Fischer 2000]. If the test
passes, the curve's maximum squared distance to the chord from its first to its
last control point is less than squared_distance_bound.

@param[in] C  4 by dim matrix of control points for a cubic Bézier curve
@param[in] squared_distance_bound  squared distance tolerance
@return True if the curve is flat within the given tolerance)");
}
