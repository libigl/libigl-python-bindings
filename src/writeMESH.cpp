#include "default_types.h"
#include <igl/writeMESH.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void writeMESH(
    const std::filesystem::path &mesh_file_name,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &T,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    if (!igl::writeMESH(mesh_file_name.generic_string(), V, T, F))
    {
      throw std::runtime_error("Failed to write .mesh file: " + mesh_file_name.generic_string());
    }
  }
}

// Bind the wrapper to the Python module
void bind_writeMESH(nb::module_ &m)
{
  m.def(
    "writeMESH",
    &pyigl::writeMESH,
    "mesh_file_name"_a,
    "V"_a=Eigen::MatrixXN(),
    "T"_a=Eigen::MatrixXI(),
    "F"_a=Eigen::MatrixXI(),
R"(Save a tetrahedral volume mesh to a .mesh file.

@param[in] mesh_file_name  Path to the .mesh file to save
@param[in] V  #V by 3 matrix of vertex positions
@param[in] T  #T by 4 matrix of tetrahedral indices
@param[in] F  #F by 3 matrix of face indices
@throws std::runtime_error if file writing fails
)");
}
