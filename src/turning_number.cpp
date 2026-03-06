#include "default_types.h"
#include <igl/turning_number.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_turning_number(nb::module_ &m)
{
  m.def("turning_number",
    [](const nb::DRef<const Eigen::MatrixXN> &V) -> Numeric {
      return igl::turning_number(V);
    },
    "V"_a,
    R"(Compute the turning number of a closed curve in the plane.

@param[in] V  #V by 2 list of 2D vertex positions forming a closed polygon
@return turning number (integer for simple closed curves))");
}
