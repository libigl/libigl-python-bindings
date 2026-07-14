#include "default_types.h"
#include <igl/predicates/insphere.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  igl::predicates::Orientation insphere(
    const Eigen::Vector3d &pa,
    const Eigen::Vector3d &pb,
    const Eigen::Vector3d &pc,
    const Eigen::Vector3d &pd,
    const Eigen::Vector3d &pe)
  {
    return igl::predicates::insphere(pa, pb, pc, pd, pe);
  }
}

void bind_insphere(nb::module_ &m)
{
  m.def(
    "insphere",
    &pyigl::insphere,
    "pa"_a, "pb"_a, "pc"_a, "pd"_a, "pe"_a,
R"(Decide whether a 3D point is inside/outside/on a sphere.

Uses exact arithmetic (Shewchuk predicates).

@param[in] pa  3D point on sphere
@param[in] pb  3D point on sphere
@param[in] pc  3D point on sphere
@param[in] pd  3D point on sphere
@param[in] pe  3D query point
@return INSIDE if pe is inside the sphere defined by pa,pb,pc,pd,
  OUTSIDE if outside, COSPHERICAL if exactly on the sphere.)");
}
