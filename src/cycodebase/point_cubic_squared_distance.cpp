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
}
