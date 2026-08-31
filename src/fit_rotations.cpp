#include "default_types.h"
#include <igl/fit_rotations.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto fit_rotations(
    const nb::DRef<const Eigen::MatrixXN> &S,
    const bool single_precision)
  {
    Eigen::MatrixXN R;
    igl::fit_rotations(S, single_precision, R);
    return R;
  }
}

void bind_fit_rotations(nb::module_ &m)
{
  m.def(
    "fit_rotations",
    &pyigl::fit_rotations,
    "S"_a,
    "single_precision"_a = false,
R"(Given a stack of covariance matrices, find the closest rotation to each
(e.g. the local step of an as-rigid-as-possible optimization).

@param[in] S  (n*dim) by dim stack of covariance matrices
@param[in] single_precision  whether to use single precision (faster)
@param[out] R  dim by (dim*n) list of rotations)");
}
