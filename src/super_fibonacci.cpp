#include "default_types.h"
#include <igl/super_fibonacci.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto super_fibonacci(const int n)
  {
    Eigen::MatrixXN Q;
    igl::super_fibonacci(n, Q);
    return Q;
  }
}

void bind_super_fibonacci(nb::module_ &m)
{
  m.def("super_fibonacci", &pyigl::super_fibonacci, "n"_a,
    R"doc(Generate n quaternions using Super-Fibonacci Spirals for low-discrepancy SO(3) sampling.

Reference: Super-Fibonacci Spirals: Fast, Low-Discrepancy Sampling of SO(3) [Alexa 2021].

@param[in] n  number of rotations to generate
@return Q  n by 4 list of unit quaternions (x, y, z, w))doc");
}
