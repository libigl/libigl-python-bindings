#include "default_types.h"
#include <igl/predicates/orient2d.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  igl::predicates::Orientation orient2d(
    const Eigen::Vector2d &pa,
    const Eigen::Vector2d &pb,
    const Eigen::Vector2d &pc)
  {
    return igl::predicates::orient2d(pa, pb, pc);
  }
}

void bind_orient2d(nb::module_ &m)
{
  m.def(
    "orient2d",
    &pyigl::orient2d,
    "pa"_a, "pb"_a, "pc"_a,
R"(Compute the orientation of the triangle formed by pa, pb, pc.

Uses exact arithmetic (Shewchuk predicates).

@param[in] pa  2D point
@param[in] pb  2D point
@param[in] pc  2D point
@return POSITIVE if pa,pb,pc are counterclockwise, NEGATIVE if clockwise,
  COLLINEAR if collinear.)");
}
