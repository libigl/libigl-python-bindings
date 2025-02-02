#include "default_types.h"
#include <igl/copyleft/cgal/convex_hull.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Second overload: convex_hull with only output F
  auto convex_hull(const nb::DRef<const Eigen::MatrixXN> &V)
  {
    Eigen::MatrixXI F;
    igl::copyleft::cgal::convex_hull(V, F);
    return F;
  }
}

// Bind the wrapper to the Python module
void bind_convex_hull(nb::module_ &m)
{
  m.def(
    "convex_hull",
    &pyigl::convex_hull,
    "V"_a,
    R"(Compute the convex hull of a set of points, returning only the triangular faces of the hull.

    @param[in] V  #V by 3 matrix of input points
    @return F: #F by 3 matrix of triangle indices into V)");
}
