#include "default_types.h"
#include <igl/cycodebase/point_cubic_squared_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto point_cubic_squared_distance(
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    Eigen::VectorXN sqrD, S;
    Eigen::MatrixXN K;
    igl::cycodebase::point_cubic_squared_distance(Q, C, sqrD, S, K);
    return std::make_tuple(sqrD, S, K);
  }

  // Precomputed overload: reuse the monomial bases (D, B) from
  // igl.cubic_monomial_bases so repeated queries don't recompute them.
  auto point_cubic_squared_distance_bases(
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &D,
    const nb::DRef<const Eigen::VectorXN> &B)
  {
    Eigen::VectorXN sqrD, S;
    Eigen::MatrixXN K;
    igl::cycodebase::point_cubic_squared_distance(Q, C, D, B, sqrD, S, K);
    return std::make_tuple(sqrD, S, K);
  }
}

void bind_point_cubic_squared_distance(nb::module_ &m)
{
  m.def("point_cubic_squared_distance", &pyigl::point_cubic_squared_distance,
    "Q"_a, "C"_a,
    R"(Squared distance from each query point to a cubic Bézier curve.

@param[in] Q  #Q by dim matrix of query points
@param[in] C  4 by dim matrix of control points for the cubic Bézier curve
@return Tuple (sqrD, S, K) where
  sqrD  #Q vector of smallest squared distances
  S     #Q vector of parameters of the closest points on the curve
  K     #Q by dim matrix of closest points on the curve)");

  m.def("point_cubic_squared_distance", &pyigl::point_cubic_squared_distance_bases,
    "Q"_a, "C"_a, "D"_a, "B"_a,
    R"(Squared distance to a cubic Bézier curve, reusing precomputed monomial bases.

Compute the bases once with igl.cubic_monomial_bases(C) -> (M, D, B) and pass
(D, B) here so repeated queries against the same curve skip recomputing them.
The result matches the two-argument overload.

@param[in] Q  #Q by dim matrix of query points
@param[in] C  4 by dim matrix of control points for the cubic Bézier curve
@param[in] D  3 by dim matrix of monomial coefficients for dC/dt (from cubic_monomial_bases)
@param[in] B  6-vector of inner products of the monomial bases (from cubic_monomial_bases)
@return Tuple (sqrD, S, K) where
  sqrD  #Q vector of smallest squared distances
  S     #Q vector of parameters of the closest points on the curve
  K     #Q by dim matrix of closest points on the curve)");
}
