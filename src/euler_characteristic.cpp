#include "default_types.h"
#include <igl/euler_characteristic.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_euler_characteristic(nb::module_ &m)
{
  m.def("euler_characteristic",
    [](const nb::DRef<const Eigen::MatrixXI> &F) -> int {
      return igl::euler_characteristic(F);
    },
    "F"_a,
    R"(Compute the Euler characteristic of a mesh: χ = |V| - |E| + |F|

@param[in] F  #F by dim list of mesh faces
@return Euler characteristic (e.g. 2 for a closed genus-0 surface))");
}
