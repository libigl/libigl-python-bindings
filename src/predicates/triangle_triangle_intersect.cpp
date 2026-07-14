#include "default_types.h"
#include <igl/predicates/triangle_triangle_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  std::tuple<bool, bool> triangle_triangle_intersect(
    const Eigen::Vector3d &a1,
    const Eigen::Vector3d &a2,
    const Eigen::Vector3d &a3,
    const Eigen::Vector3d &b1,
    const Eigen::Vector3d &b2,
    const Eigen::Vector3d &b3)
  {
    bool coplanar = false;
    bool result = igl::predicates::triangle_triangle_intersect(
      a1, a2, a3, b1, b2, b3, coplanar);
    return {result, coplanar};
  }
}

void bind_triangle_triangle_intersect(nb::module_ &m)
{
  m.def(
    "triangle_triangle_intersect",
    &pyigl::triangle_triangle_intersect,
    "a1"_a, "a2"_a, "a3"_a, "b1"_a, "b2"_a, "b3"_a,
R"(Test whether two 3D triangles intersect using exact predicates.

@param[in] a1  1st vertex of triangle A
@param[in] a2  2nd vertex of triangle A
@param[in] a3  3rd vertex of triangle A
@param[in] b1  1st vertex of triangle B
@param[in] b2  2nd vertex of triangle B
@param[in] b3  3rd vertex of triangle B
@return (intersects, coplanar) where intersects is true if the triangles
  intersect, and coplanar is true if they are coplanar.)");
}
