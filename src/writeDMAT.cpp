#include "default_types.h"
#include <igl/writeDMAT.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/filesystem.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for writeDMAT with Eigen matrix input
  bool writeDMAT(
    const std::filesystem::path &file_name,
    const nb::DRef<const Eigen::MatrixXN> &W, 
    const bool ascii)
  {
    if (!igl::writeDMAT(file_name.generic_string(), W, ascii))
    {
      throw std::runtime_error("writeDMAT: Failed to write DMAT file.");
    }
    return true;
  }
}

// Bind the wrappers to the Python module
void bind_writeDMAT(nb::module_ &m)
{
  m.def(
    "writeDMAT",
    &pyigl::writeDMAT,
    "file_name"_a,
    "W"_a,
    "ascii"_a = true,
    R"(Write a matrix to a .dmat file in ASCII or binary format.

    @param[in] file_name  path to .dmat file
    @param[in] W  Eigen matrix containing coefficients to write
    @param[in] ascii  flag for ASCII format (default: true)
    @return True if the operation is successful)");
}
