#include "default_types.h"
#include <igl/copyleft/cgal/intersect_with_half_space.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Overload with point and normal
  auto intersect_with_half_space_point_normal(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &p,
    const nb::DRef<const Eigen::VectorXN> &n)
  {
    Eigen::MatrixXN VC;
    Eigen::MatrixXI FC;
    Eigen::VectorXI J;

    if(!igl::copyleft::cgal::intersect_with_half_space(V, F, p, n, VC, FC, J))
    {
      throw std::runtime_error("Failed to intersect with half space");
    }
    return std::make_tuple(VC, FC, J);
  }

  // Overload with plane equation
  auto intersect_with_half_space_equation(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &equ)
  {
    Eigen::MatrixXN VC;
    Eigen::MatrixXI FC;
    Eigen::VectorXI J;

    if(!igl::copyleft::cgal::intersect_with_half_space(V, F, equ, VC, FC, J))
    {
      throw std::runtime_error("Failed to intersect with half space");
    }
    return std::make_tuple( VC, FC, J);
  }

}

// Bind the wrapper to the Python module
void bind_intersect_with_half_space(nb::module_ &m)
{
  m.def(
    "intersect_with_half_space",
    &pyigl::intersect_with_half_space_point_normal,
    "V"_a,
    "F"_a,
    "p"_a,
    "n"_a,
    R"(Intersect a PWN mesh with a half-space using a point and normal.

    @param[in] V  #V by 3 list of mesh vertex positions
    @param[in] F  #F by 3 list of triangle indices
    @param[in] p  3D point on plane
    @param[in] n  3D normal vector
    @return Tuple containing:
      - success: bool, true if successful
      - VC: vertices of resulting mesh
      - FC: face indices of resulting mesh
      - J: birth facet indices)");

  m.def(
    "intersect_with_half_space",
    &pyigl::intersect_with_half_space_equation,
    "V"_a,
    "F"_a,
    "equ"_a,
    R"(Intersect a PWN mesh with a half-space using the plane equation.

    @param[in] V  #V by 3 list of mesh vertex positions
    @param[in] F  #F by 3 list of triangle indices
    @param[in] equ  Plane equation coefficients (a, b, c, d)
    @return Tuple containing:
      - success: bool, true if successful
      - VC: vertices of resulting mesh
      - FC: face indices of resulting mesh
      - J: birth facet indices)");
}
