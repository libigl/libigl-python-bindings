#include "default_types.h"
#include <igl/fit_plane.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto fit_plane(const nb::DRef<const Eigen::MatrixXN> &V)
  {
    Eigen::RowVector3d N, C;
    igl::fit_plane(V, N, C);
    return std::make_tuple(
      Eigen::VectorXN(N.transpose()),
      Eigen::VectorXN(C.transpose()));
  }
}

void bind_fit_plane(nb::module_ &m)
{
  m.def("fit_plane", &pyigl::fit_plane, "V"_a,
    R"(Fit a plane to a point cloud.

@param[in] V  #V by 3 matrix of 3D point cloud positions
@return N  3-vector normal of the fitted plane
@return C  3-vector of a point that lies on the fitted plane)");
}
