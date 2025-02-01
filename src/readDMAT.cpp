#include "default_types.h"
#include <igl/readDMAT.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for readDMAT with Eigen matrix output
  Eigen::MatrixXN readDMAT(const std::filesystem::path &file_name)
  {
    Eigen::MatrixXN W;
    if (!igl::readDMAT(file_name.generic_string(), W))
    {
      throw std::runtime_error("readDMAT: Failed to read DMAT file.");
    }
    return W;
  }

}

// Bind the wrapper to the Python module
void bind_readDMAT(nb::module_ &m)
{
  m.def(
    "readDMAT",
    &pyigl::readDMAT,
    "file_name"_a,
    R"(Read a matrix from a .dmat file.

    @param[in] file_name  path to .dmat file
    @return Eigen matrix containing read-in coefficients
    )");

}
