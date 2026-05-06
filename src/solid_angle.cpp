#include "default_types.h"
#include <igl/solid_angle.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto solid_angle(
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &P)
  {
    // igl uses single-index access — copy to VectorXd
    const Eigen::VectorXd a = A.reshaped(), b = B.reshaped();
    const Eigen::VectorXd c = C.reshaped(), p = P.reshaped();
    return igl::solid_angle(a, b, c, p);
  }
}

void bind_solid_angle(nb::module_ &m)
{
  m.def("solid_angle", &pyigl::solid_angle,
    "A"_a, "B"_a, "C"_a, "P"_a,
    R"(Compute the signed solid angle subtended by oriented triangle (A,B,C) at point P.

@param[in] A  3D position of first corner
@param[in] B  3D position of second corner
@param[in] C  3D position of third corner
@param[in] P  3D position of query point
@return signed solid angle in steradians)");
}
