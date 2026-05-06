#include "default_types.h"
#include <igl/barycentric_interpolation.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto barycentric_interpolation(
    const nb::DRef<const Eigen::MatrixXN> &D,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXI> &I)
  {
    // I is indexed as a vector internally
    const Eigen::VectorXI idx = I.reshaped();
    Eigen::MatrixXN X;
    igl::barycentric_interpolation(D, F, B, idx, X);
    return X;
  }
}

void bind_barycentric_interpolation(nb::module_ &m)
{
  m.def("barycentric_interpolation", &pyigl::barycentric_interpolation,
    "D"_a, "F"_a, "B"_a, "I"_a,
    R"(Interpolate per-vertex data on a triangle mesh using barycentric coordinates.

@param[in] D  #V by dim list of per-vertex data
@param[in] F  #F by 3 list of triangle indices
@param[in] B  #X by 3 list of barycentric coordinates
@param[in] I  #X list of triangle indices into F
@return X  #X by dim list of interpolated data)");
}
