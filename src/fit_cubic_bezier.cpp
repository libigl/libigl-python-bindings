#include "default_types.h"
#include <igl/fit_cubic_bezier.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto fit_cubic_bezier(
    const nb::DRef<const Eigen::MatrixXN> &d,
    const Numeric error)
  {
    // fit_cubic_bezier takes a concrete Eigen::MatrixXd (column-major)
    const Eigen::MatrixXd D = d;
    std::vector<Eigen::MatrixXd> cubics;
    igl::fit_cubic_bezier(D, error, cubics);
    return cubics;
  }
}

void bind_fit_cubic_bezier(nb::module_ &m)
{
  m.def("fit_cubic_bezier", &pyigl::fit_cubic_bezier, "d"_a, "error"_a,
    R"(Fit a G1-continuous cubic Bézier spline to an ordered list of points.

According to "An algorithm for automatically fitting digitized curves"
[Schneider 1990].

@param[in] d  #d by dim list of points along a curve (roughly uniformly spaced).
  If d[0]==d[-1] the curve is treated as closed.
@param[in] error  maximum squared distance allowed
@return cubics  list of 4 by dim arrays of cubic Bézier control points)");
}
