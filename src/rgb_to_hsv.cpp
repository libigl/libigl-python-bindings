#include "default_types.h"
#include <igl/rgb_to_hsv.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto rgb_to_hsv(const nb::DRef<const Eigen::MatrixXN> &R)
  {
    Eigen::MatrixXN H;
    igl::rgb_to_hsv(R, H);
    return H;
  }
}

void bind_rgb_to_hsv(nb::module_ &m)
{
  m.def("rgb_to_hsv", &pyigl::rgb_to_hsv, "R"_a,
    R"(Convert RGB colors to HSV.

@param[in] R  #R by 3 list of RGB values in [0,1]
@return H  #R by 3 list of HSV values: h in [0,360], s in [0,1], v in [0,1])");
}
