#include "default_types.h"
#include <igl/predicates/point_in_convex_hull.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  igl::Orientation point_in_convex_hull(
    const Eigen::RowVector2d &q,
    const Eigen::RowVector2d &a,
    const Eigen::RowVector2d &b,
    const Eigen::RowVector2d &c,
    const Eigen::RowVector2d &d)
  {
    return igl::predicates::point_in_convex_hull(q, a, b, c, d);
  }
}

void bind_point_in_convex_hull(nb::module_ &m)
{
  m.def("point_in_convex_hull", &pyigl::point_in_convex_hull,
    "q"_a, "a"_a, "b"_a, "c"_a, "d"_a,
    R"(Test whether a 2D point lies in the convex hull of four points using exact predicates.

@param[in] q  2D query point
@param[in] a  2D point
@param[in] b  2D point
@param[in] c  2D point
@param[in] d  2D point
@return POSITIVE if q is strictly inside the convex hull of {a,b,c,d},
  NEGATIVE if strictly outside, COLLINEAR if on the boundary.)");
}
