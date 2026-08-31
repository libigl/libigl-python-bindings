#include "default_types.h"
#include <igl/polar_svd3x3.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto polar_svd3x3(const nb::DRef<const Eigen::MatrixXN> &A)
  {
    Eigen::Matrix<Numeric, 3, 3> Am = A;
    Eigen::Matrix<Numeric, 3, 3> R;
    igl::polar_svd3x3(Am, R);
    return Eigen::MatrixXN(R);
  }
}

void bind_polar_svd3x3(nb::module_ &m)
{
  m.def(
    "polar_svd3x3",
    &pyigl::polar_svd3x3,
    "A"_a,
R"(Compute the closest rotation matrix R to a 3x3 matrix A via the polar
decomposition (using a fast fixed-size SVD).

@param[in] A  3 by 3 matrix
@param[out] R  3 by 3 closest rotation matrix (det(R) = +1))");
}
