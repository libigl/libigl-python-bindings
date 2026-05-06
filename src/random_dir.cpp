#include "default_types.h"
#include <igl/random_dir.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_random_dir(nb::module_ &m)
{
  m.def("random_dir",
    []() -> Eigen::VectorXN {
      return igl::random_dir().cast<Numeric>();
    },
    R"(Generate a uniformly random unit direction in 3D.

@return 3-vector random unit direction)");

  m.def("random_dir_stratified",
    [](const int n) -> Eigen::MatrixXN {
      return igl::random_dir_stratified(n).cast<Numeric>();
    },
    "n"_a,
    R"(Generate n stratified uniformly random unit directions in 3D.

@param[in] n  number of directions
@return n by 3 matrix of random unit directions)");
}
