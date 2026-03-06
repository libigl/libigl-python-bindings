#include "default_types.h"
#include <igl/ray_triangle_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto ray_triangle_intersect(
    const nb::DRef<const Eigen::MatrixXN> &O,
    const nb::DRef<const Eigen::MatrixXN> &D,
    const nb::DRef<const Eigen::MatrixXN> &V0,
    const nb::DRef<const Eigen::MatrixXN> &V1,
    const nb::DRef<const Eigen::MatrixXN> &V2,
    const Numeric epsilon)
  {
    // igl requires vector types (Dynamic×1 or similar) — copy from 2D DRef
    const Eigen::VectorXd o = O.reshaped();
    const Eigen::VectorXd d = D.reshaped();
    const Eigen::VectorXd v0 = V0.reshaped();
    const Eigen::VectorXd v1 = V1.reshaped();
    const Eigen::VectorXd v2 = V2.reshaped();
    Numeric t, u, v;
    bool parallel;
    bool hit = igl::ray_triangle_intersect(o, d, v0, v1, v2, epsilon, t, u, v, parallel);
    return std::make_tuple(hit, t, u, v, parallel);
  }
}

void bind_ray_triangle_intersect(nb::module_ &m)
{
  m.def("ray_triangle_intersect", &pyigl::ray_triangle_intersect,
    "O"_a, "D"_a, "V0"_a, "V1"_a, "V2"_a, "epsilon"_a = 1e-10,
    R"(Determine whether a ray intersects a triangle.

@param[in] O  3-vector ray origin
@param[in] D  3-vector ray direction
@param[in] V0  3-vector first triangle vertex
@param[in] V1  3-vector second triangle vertex
@param[in] V2  3-vector third triangle vertex
@param[in] epsilon  tolerance for parallel check
@return hit  true if ray intersects triangle
@return t  distance along ray to intersection
@return u  barycentric coordinate of V1
@return v  barycentric coordinate of V2
@return parallel  true if ray is parallel to triangle)");
}
