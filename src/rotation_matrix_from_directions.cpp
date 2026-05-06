#include "default_types.h"
#include <igl/rotation_matrix_from_directions.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto rotation_matrix_from_directions(
    const nb::DRef<const Eigen::MatrixXN> &v0,
    const nb::DRef<const Eigen::MatrixXN> &v1)
  {
    Eigen::Matrix<Numeric, 3, 1> a = v0.reshaped(3,1);
    Eigen::Matrix<Numeric, 3, 1> b = v1.reshaped(3,1);
    return Eigen::MatrixXN(igl::rotation_matrix_from_directions(a, b));
  }
}

void bind_rotation_matrix_from_directions(nb::module_ &m)
{
  m.def("rotation_matrix_from_directions",
    &pyigl::rotation_matrix_from_directions,
    "v0"_a, "v1"_a,
    R"(Compute the rotation matrix that rotates unit vector v0 to unit vector v1.

@param[in] v0  3-vector source direction
@param[in] v1  3-vector target direction
@return 3 by 3 rotation matrix R such that R*v0 ≈ v1)");
}
