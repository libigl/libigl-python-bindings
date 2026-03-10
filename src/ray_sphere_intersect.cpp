#include "default_types.h"
#include <igl/ray_sphere_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto ray_sphere_intersect(
    const nb::DRef<const Eigen::MatrixXN> &o,
    const nb::DRef<const Eigen::MatrixXN> &d,
    const nb::DRef<const Eigen::MatrixXN> &c,
    const Numeric r)
  {
    // igl uses .dot() which requires IsVectorAtCompileTime — copy to VectorXd
    const Eigen::VectorXd ov = o.reshaped();
    const Eigen::VectorXd dv = d.reshaped();
    const Eigen::VectorXd cv = c.reshaped();
    Numeric t0, t1;
    int n = igl::ray_sphere_intersect(ov, dv, cv, r, t0, t1);
    return std::make_tuple(n, t0, t1);
  }
}

void bind_ray_sphere_intersect(nb::module_ &m)
{
  m.def("ray_sphere_intersect", &pyigl::ray_sphere_intersect,
    "o"_a, "d"_a, "c"_a, "r"_a,
    R"(Compute intersection(s) between a ray and a sphere.

@param[in] o  3-vector ray origin
@param[in] d  3-vector ray direction
@param[in] c  3-vector sphere center
@param[in] r  sphere radius
@return n   number of intersections (0, 1, or 2)
@return t0  parameter of first hit: hit = o + t0*d
@return t1  parameter of second hit)");
}
