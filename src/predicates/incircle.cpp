#include "default_types.h"
#include <igl/predicates/incircle.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  igl::predicates::Orientation incircle(
    const Eigen::Vector2d &pa,
    const Eigen::Vector2d &pb,
    const Eigen::Vector2d &pc,
    const Eigen::Vector2d &pd)
  {
    return igl::predicates::incircle(pa, pb, pc, pd);
  }
}

void bind_incircle(nb::module_ &m)
{
  m.def(
    "incircle",
    &pyigl::incircle,
    "pa"_a, "pb"_a, "pc"_a, "pd"_a,
R"(Decide whether a 2D point is inside/outside/on a circle.

Uses exact arithmetic (Shewchuk predicates).

@param[in] pa  2D point on circle
@param[in] pb  2D point on circle
@param[in] pc  2D point on circle
@param[in] pd  2D query point
@return INSIDE if pd is inside the circle defined by pa,pb,pc,
  OUTSIDE if outside, COCIRCULAR if exactly on the circle.)");
}
