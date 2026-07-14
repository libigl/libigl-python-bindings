#include "default_types.h"
#include <igl/predicates/point_inside_convex_polygon.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool point_inside_convex_polygon(
    const Eigen::MatrixX2d &P,
    const Eigen::RowVector2d &q)
  {
    return igl::predicates::point_inside_convex_polygon(P, q);
  }
}

void bind_point_inside_convex_polygon(nb::module_ &m)
{
  m.def(
    "point_inside_convex_polygon",
    &pyigl::point_inside_convex_polygon,
    "P"_a, "q"_a,
R"(Check whether a 2D point lies inside a 2D convex polygon.

@param[in] P  #P by 2 list of polygon vertices (n >= 3)
@param[in] q  2D query point
@return true if q is inside P.)");
}
