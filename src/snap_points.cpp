#include "default_types.h"
#include <igl/snap_points.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto snap_points(
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &V)
  {
    Eigen::VectorXI I;
    Eigen::VectorXN minD;
    Eigen::MatrixXN VI;
    igl::snap_points(C, V, I, minD, VI);
    return std::make_tuple(I, minD, VI);
  }
}

void bind_snap_points(nb::module_ &m)
{
  m.def("snap_points", &pyigl::snap_points, "C"_a, "V"_a,
    R"(Snap query points C to the closest points in V.

@param[in] C  #C by dim list of query positions
@param[in] V  #V by dim list of data positions
@return I    #C list of indices into V of closest points
@return minD #C list of squared distances to closest points
@return VI   #C by dim list of snapped positions (VI = V(I,:)))");
}
