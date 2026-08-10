#include "default_types.h"
#include <igl/cubic_split.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cubic_split(
    const nb::DRef<const Eigen::MatrixXN> &C,
    const Numeric t)
  {
    Eigen::MatrixXN C1, C2;
    igl::cubic_split(C, t, C1, C2);
    return std::make_tuple(C1, C2);
  }
}

void bind_cubic_split(nb::module_ &m)
{
  m.def("cubic_split", &pyigl::cubic_split, "C"_a, "t"_a,
    R"(Split a cubic Bézier curve at parameter t into two cubic Bézier curves.

@param[in] C  4 by dim matrix of control points for a cubic Bézier curve
@param[in] t  parameter at which to split the curve
@return Tuple (C1, C2) where
  C1  4 by dim control points of the sub-curve from C(0) to C(t)
  C2  4 by dim control points of the sub-curve from C(t) to C(1))");
}
