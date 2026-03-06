#include "default_types.h"
#include <igl/signed_angle.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto signed_angle(
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &P)
  {
    // igl uses single-index access — copy to VectorXd
    const Eigen::VectorXd a = A.reshaped(), b = B.reshaped(), p = P.reshaped();
    return igl::signed_angle(a, b, p);
  }
}

void bind_signed_angle(nb::module_ &m)
{
  m.def("signed_angle", &pyigl::signed_angle,
    "A"_a, "B"_a, "P"_a,
    R"(Compute the signed angle subtended by segment AB at point P in 2D.

@param[in] A  2D position of first endpoint
@param[in] B  2D position of second endpoint
@param[in] P  2D position of query point
@return signed angle in radians)");
}
