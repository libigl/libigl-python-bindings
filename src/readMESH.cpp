#include "default_types.h"
#include <igl/readMESH.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/tuple.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readMESH(const std::filesystem::path& mesh_file_name)
  {
    Eigen::MatrixXN V;  // Vertex positions
    Eigen::MatrixXI T;  // Tetrahedral indices
    Eigen::MatrixXI F;  // Face indices

    if (!igl::readMESH(mesh_file_name.generic_string(), V, T, F))
    {
      throw std::runtime_error("Failed to read .mesh file: " + mesh_file_name.generic_string());
    }

    return std::make_tuple(V, T, F);
  }
}

// Bind the wrapper to the Python module
void bind_readMESH(nb::module_ &m)
{
  m.def(
    "readMESH",
    &pyigl::readMESH,
    "mesh_file_name"_a,
R"(Load a tetrahedral volume mesh from a .mesh file.

@param[in] mesh_file_name  Path of the .mesh file to read
@return Tuple containing:
  - V: #V by 3 matrix of vertex positions
  - T: #T by 4 matrix of tetrahedral indices into vertices
  - F: #F by 3 matrix of face indices into vertices
@throws std::runtime_error if file reading fails
)");
}
