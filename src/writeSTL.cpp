#include "default_types.h"
#include <igl/writeSTL.h>
#include <igl/FileEncoding.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool writeSTL(
    const std::string &filename,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const bool binary)
  {
    auto enc = binary ? igl::FileEncoding::Binary : igl::FileEncoding::Ascii;
    if (!igl::writeSTL(filename, V, F, enc))
      throw std::runtime_error("Failed to write STL file: " + filename);
    return true;
  }
}

void bind_writeSTL(nb::module_ &m)
{
  m.def("writeSTL", &pyigl::writeSTL,
    "filename"_a, "V"_a, "F"_a, "binary"_a = false,
    R"(Write a mesh to an STL file.

@param[in] filename  path to .stl output file
@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] binary  if true, write binary STL; otherwise ASCII
@return true on success (raises on failure))");
}
