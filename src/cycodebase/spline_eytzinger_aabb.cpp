#include "default_types.h"
#include <igl/cycodebase/spline_eytzinger_aabb.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto spline_eytzinger_aabb(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &C)
  {
    Eigen::MatrixXN B1, B2;
    Eigen::VectorXI leaf;
    igl::cycodebase::spline_eytzinger_aabb(P, C, B1, B2, leaf);
    return std::make_tuple(B1, B2, leaf);
  }
}

void bind_spline_eytzinger_aabb(nb::module_ &m)
{
  m.def("spline_eytzinger_aabb", &pyigl::spline_eytzinger_aabb, "P"_a, "C"_a,
    R"(Compute an Eytzinger-layout AABB tree for a spline of cubic Bézier curves.

@param[in] P  #P by dim matrix of spline control points
@param[in] C  #C by 4 matrix of indices into P defining the cubic Bézier curves
@return Tuple (B1, B2, leaf) where
  B1    #B by dim matrix of AABB min box corners
  B2    #B by dim matrix of AABB max box corners
  leaf  #B vector of AABB leaf node indices/flags)");
}
