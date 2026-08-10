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
}
