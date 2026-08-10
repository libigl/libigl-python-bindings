#include "default_types.h"
#include <igl/cubic.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cubic(
    const nb::DRef<const Eigen::MatrixXN> &C,
    const Numeric t)
  {
    Eigen::MatrixXN P;
    igl::cubic(C, t, P);
    return P;
  }
}

void bind_cubic(nb::module_ &m)
{
  m.def("cubic", &pyigl::cubic, "C"_a, "t"_a,
    R"(Evaluate a cubic Bézier curve defined by control points C at parameter t.

@param[in] C  4 by dim matrix of control points for a cubic Bézier curve
@param[in] t  parameter at which to evaluate the curve
@return P  1 by dim point on the curve C(t))");
}
