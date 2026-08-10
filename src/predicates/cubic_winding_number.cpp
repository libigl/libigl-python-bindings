#include "default_types.h"
#include <igl/predicates/cubic_winding_number.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  Numeric cubic_winding_number(
    const nb::DRef<const Eigen::MatrixXN> &C,
    const Eigen::RowVector2d &q)
  {
    return igl::predicates::cubic_winding_number(C, q);
  }
}

void bind_cubic_winding_number(nb::module_ &m)
{
  m.def("cubic_winding_number", &pyigl::cubic_winding_number, "C"_a, "q"_a,
    R"(Exact winding number of a 2D cubic Bézier curve about a query point.

@param[in] C  4 by 2 matrix of control points for the cubic Bézier curve
@param[in] q  2D query point
@return the (fractional) winding number of the curve about q)");
}
