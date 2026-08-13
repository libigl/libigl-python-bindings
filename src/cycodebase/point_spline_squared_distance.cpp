#include "default_types.h"
#include <igl/cycodebase/point_spline_squared_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto point_spline_squared_distance(
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &C)
  {
    Eigen::VectorXN sqrD, S;
    Eigen::VectorXI I;
    Eigen::MatrixXN K;
    igl::cycodebase::point_spline_squared_distance(Q, P, C, sqrD, I, S, K);
    return std::make_tuple(sqrD, I, S, K);
  }

  // Accelerated overload: reuse a prebuilt Eytzinger AABB (B1, B2, leaf) from
  // igl.cycodebase.spline_eytzinger_aabb so repeated queries don't rebuild it.
  auto point_spline_squared_distance_aabb(
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &C,
    const nb::DRef<const Eigen::MatrixXN> &B1,
    const nb::DRef<const Eigen::MatrixXN> &B2,
    const nb::DRef<const Eigen::VectorXI> &leaf)
  {
    Eigen::VectorXN sqrD, S;
    Eigen::VectorXI I;
    Eigen::MatrixXN K;
    igl::cycodebase::point_spline_squared_distance(
      Q, P, C, B1, B2, leaf, sqrD, I, S, K);
    return std::make_tuple(sqrD, I, S, K);
  }
}

void bind_point_spline_squared_distance(nb::module_ &m)
{
  m.def("point_spline_squared_distance", &pyigl::point_spline_squared_distance,
    "Q"_a, "P"_a, "C"_a,
    R"(Squared distance from each query point to a spline of cubic Bézier curves.

@param[in] Q  #Q by dim matrix of query points
@param[in] P  #P by dim matrix of spline control points
@param[in] C  #C by 4 matrix of indices into P defining the cubic Bézier curves
@return Tuple (sqrD, I, S, K) where
  sqrD  #Q vector of smallest squared distances
  I     #Q vector of indices of the closest cubic (row of C)
  S     #Q vector of parameters of the closest points on that cubic
  K     #Q by dim matrix of closest points on the spline)");

  m.def("point_spline_squared_distance", &pyigl::point_spline_squared_distance_aabb,
    "Q"_a, "P"_a, "C"_a, "B1"_a, "B2"_a, "leaf"_a,
    R"(Squared distance to a spline, reusing a prebuilt Eytzinger AABB.

Build the AABB once with igl.cycodebase.spline_eytzinger_aabb(P, C) and pass its
(B1, B2, leaf) here so repeated queries against the same spline skip rebuilding
the acceleration structure. The result matches the unaccelerated overload.

@param[in] Q     #Q by dim matrix of query points
@param[in] P     #P by dim matrix of spline control points
@param[in] C     #C by 4 matrix of indices into P defining the cubic Bézier curves
@param[in] B1    #B by dim matrix of AABB min box corners (from spline_eytzinger_aabb)
@param[in] B2    #B by dim matrix of AABB max box corners (from spline_eytzinger_aabb)
@param[in] leaf  #B vector of AABB leaf node indices/flags (from spline_eytzinger_aabb)
@return Tuple (sqrD, I, S, K) where
  sqrD  #Q vector of smallest squared distances
  I     #Q vector of indices of the closest cubic (row of C)
  S     #Q vector of parameters of the closest points on that cubic
  K     #Q by dim matrix of closest points on the spline)");
}
