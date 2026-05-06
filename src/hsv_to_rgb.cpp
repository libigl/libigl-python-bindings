#include "default_types.h"
#include <igl/hsv_to_rgb.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto hsv_to_rgb(const nb::DRef<const Eigen::MatrixXN> &H)
  {
    Eigen::MatrixXN R;
    igl::hsv_to_rgb(H, R);
    return R;
  }
}

void bind_hsv_to_rgb(nb::module_ &m)
{
  m.def("hsv_to_rgb", &pyigl::hsv_to_rgb, "H"_a,
    R"(Convert HSV colors to RGB.

@param[in] H  #H by 3 list of HSV values: h in [0,360], s in [0,1], v in [0,1]
@return R  #H by 3 list of RGB values in [0,1])");
}
