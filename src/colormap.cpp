#include "default_types.h"
#include <igl/colormap.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Map scalar array to RGB colors using a colormap
  auto colormap(
    const igl::ColorMapType cm,
    const nb::DRef<const Eigen::VectorXN> &Z,
    const bool normalize)
  {
    Eigen::MatrixXN C;
    igl::colormap(cm, Z, normalize, C);
    return C;
  }
  // Map scalar to single RGB triple
  auto colormap_scalar(
    const igl::ColorMapType cm,
    const Numeric f)
  {
    Numeric r, g, b;
    igl::colormap(cm, f, r, g, b);
    Eigen::Vector3d rgb;
    rgb << r, g, b;
    return rgb;
  }
}

void bind_colormap(nb::module_ &m)
{
  nb::enum_<igl::ColorMapType>(m, "ColorMapType")
    .value("INFERNO",  igl::COLOR_MAP_TYPE_INFERNO)
    .value("JET",      igl::COLOR_MAP_TYPE_JET)
    .value("MAGMA",    igl::COLOR_MAP_TYPE_MAGMA)
    .value("PARULA",   igl::COLOR_MAP_TYPE_PARULA)
    .value("PLASMA",   igl::COLOR_MAP_TYPE_PLASMA)
    .value("VIRIDIS",  igl::COLOR_MAP_TYPE_VIRIDIS)
    .value("TURBO",    igl::COLOR_MAP_TYPE_TURBO)
    .export_values();

  m.def("colormap", &pyigl::colormap,
    "cm"_a, "Z"_a, "normalize"_a = true,
    R"(Map scalar values to RGB colors using a colormap.

@param[in] cm  colormap type (igl.ColorMapType.VIRIDIS, .JET, etc.)
@param[in] Z   #Z list of scalar values
@param[in] normalize  if true, normalize Z to [0,1] range before mapping
@return C  #Z by 3 list of RGB colors in [0,1])");

  m.def("colormap", &pyigl::colormap_scalar,
    "cm"_a, "f"_a,
    R"(Map a single scalar in [0,1] to an RGB color.

@param[in] cm  colormap type
@param[in] f   scalar in [0,1]
@return 3-vector of RGB values in [0,1])");
}
