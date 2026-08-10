#include "default_types.h"
#include <igl/predicates/spline_winding_number.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto spline_winding_number(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &C,
    const nb::DRef<const Eigen::MatrixXN> &B1,
    const nb::DRef<const Eigen::MatrixXN> &B2,
    const nb::DRef<const Eigen::VectorXI> &leaf,
    const nb::DRef<const Eigen::MatrixXN> &Q)
  {
    Eigen::VectorXN W;
    igl::predicates::spline_winding_number(P, C, B1, B2, leaf, Q, W);
    return W;
  }
}

void bind_spline_winding_number(nb::module_ &m)
{
  m.def("spline_winding_number", &pyigl::spline_winding_number,
    "P"_a, "C"_a, "B1"_a, "B2"_a, "leaf"_a, "Q"_a,
    R"(Winding number of a closed spline of cubic Bézier curves about query points.

Uses the Eytzinger-layout AABB tree produced by
igl.cycodebase.spline_eytzinger_aabb for acceleration.

@param[in] P     #P by 2 matrix of spline control points
@param[in] C     #C by 4 matrix of indices into P defining the cubic Bézier curves
@param[in] B1    #B by 2 matrix of AABB min box corners
@param[in] B2    #B by 2 matrix of AABB max box corners
@param[in] leaf  #B vector of AABB leaf node indices/flags
@param[in] Q     #Q by 2 matrix of query points
@return W  #Q vector of winding numbers about each query point)");
}
