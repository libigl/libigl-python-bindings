#include "default_types.h"
#include <igl/kelvinlets.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto kelvinlets(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::VectorXN> &x0,
    const nb::DRef<const Eigen::VectorXN> &f,
    const nb::DRef<const Eigen::MatrixXN> &F,
    const Numeric epsilon,
    const Numeric falloff,
    const igl::BrushType brushType)
  {
    Eigen::MatrixXN result;
    igl::kelvinlets(
      V,
      x0,
      f,
      F,
      igl::KelvinletParams<Numeric>(epsilon, falloff, brushType),
      result);
    return result;
  }
}

// Bind the wrapper to the Python module
void bind_kelvinlets(nb::module_ &m)
{
  nb::enum_<igl::BrushType>(m, "BrushType")
    .value("GRAB", igl::BrushType::GRAB)
    .value("SCALE", igl::BrushType::SCALE)
    .value("TWIST", igl::BrushType::TWIST)
    .value("PINCH", igl::BrushType::PINCH)
    .export_values();
  m.def(
    "kelvinlets",
    &pyigl::kelvinlets, 
    "V"_a, 
    "x0"_a, 
    "f"_a, 
    "F"_a,
    "epsilon"_a =1.0,
    "falloff"_a =1.0,
    "brushType"_a=igl::BrushType::GRAB,
R"(Implements Pixar's Regularized Kelvinlets (Pixar Technical Memo #17-03):
Sculpting Brushes based on Fundamental Solutions of Elasticity, a technique
for real-time physically based volume sculpting of virtual elastic materials

@param[in] V  #V by dim list of input points in space
@param[in] x0  dim-vector of brush tip
@param[in] f  dim-vector of brush force (translation)
@param[in] F  dim by dim matrix of brush force matrix  (linear)
@param[in] params  parameters for the kelvinlet brush like brush radius, scale etc
@param[out] X  #V by dim list of output points in space
)");

}



