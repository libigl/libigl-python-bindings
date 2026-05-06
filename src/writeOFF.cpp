#include "default_types.h"
#include <igl/writeOFF.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool writeOFF(
    const std::string &filename,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    if (!igl::writeOFF(filename, V, F))
      throw std::runtime_error("Failed to write OFF file: " + filename);
    return true;
  }
  bool writeOFF_C(
    const std::string &filename,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    if (!igl::writeOFF(filename, V, F, C))
      throw std::runtime_error("Failed to write OFF file: " + filename);
    return true;
  }
}

void bind_writeOFF(nb::module_ &m)
{
  m.def("writeOFF", &pyigl::writeOFF, "filename"_a, "V"_a, "F"_a,
    R"(Write a mesh to an ASCII OFF file.

@param[in] filename  path to .off output file
@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@return true on success (raises on failure))");

  m.def("writeOFF", &pyigl::writeOFF_C,
    "filename"_a, "V"_a, "F"_a, "C"_a,
    R"(Write a mesh with per-vertex colors to an ASCII OFF file.

@param[in] filename  path to .off output file
@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] C  #V by 3 list of RGB colors in [0,1]
@return true on success (raises on failure))");
}
