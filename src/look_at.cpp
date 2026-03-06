#include "default_types.h"
#include <igl/look_at.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto look_at(
    const nb::DRef<const Eigen::MatrixXN> &eye,
    const nb::DRef<const Eigen::MatrixXN> &center,
    const nb::DRef<const Eigen::MatrixXN> &up)
  {
    // look_at uses cross() which requires IsVectorAtCompileTime — copy to Vector3d
    Eigen::Vector3d e = eye.reshaped(3,1);
    Eigen::Vector3d c = center.reshaped(3,1);
    Eigen::Vector3d u = up.reshaped(3,1);
    Eigen::Matrix4d R;
    igl::look_at(e, c, u, R);
    return Eigen::MatrixXN(R.cast<Numeric>());
  }
}

void bind_look_at(nb::module_ &m)
{
  m.def("look_at", &pyigl::look_at,
    "eye"_a, "center"_a, "up"_a,
    R"(Compute a view matrix like gluLookAt.

@param[in] eye     3-vector eye position
@param[in] center  3-vector center/target position
@param[in] up      3-vector up direction
@return R  4x4 view (rotation+translation) matrix)");
}
