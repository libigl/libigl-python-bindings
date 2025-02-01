#include "default_types.h"
#include <igl/writeMSH.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/vector.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void writeMSH(
    const std::filesystem::path &mesh_file_name,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Tri,
    const nb::DRef<const Eigen::MatrixXI> &Tet,
    const nb::DRef<const Eigen::VectorXI> &TriTag,
    const nb::DRef<const Eigen::VectorXI> &TetTag)
  {
    std::vector<Eigen::MatrixXN> XF;
    std::vector<std::string> XFields;
    std::vector<std::string> EFields;
    std::vector<Eigen::MatrixXN> TriF;
    std::vector<Eigen::MatrixXN> TetF;
    if(!igl::writeMSH(mesh_file_name.generic_string(), V, Tri, Tet, TriTag, TetTag, XFields, XF, EFields, TriF, TetF))
    {
      throw std::runtime_error("Failed to write .msh file: " + mesh_file_name.generic_string());
    }
  }
}

// Bind the wrapper to the Python module
void bind_writeMSH(nb::module_ &m)
{
  m.def(
    "writeMSH",
    &pyigl::writeMSH,
    "mesh_file_name"_a,
    "V"_a=Eigen::MatrixXN(),
    "Tri"_a=Eigen::MatrixXI(),
    "Tet"_a=Eigen::MatrixXI(),
    "TriTag"_a=Eigen::VectorXI(),
    "TetTag"_a=Eigen::VectorXI(),
R"(Save a tetrahedral volume mesh to a .msh file.

@param[in] mesh_file_name  Path to the .mesh file to save
@param[in] V  #V by 3 matrix of vertex positions
@param[in] Tri  #Tri by 3 matrix of face indices
@param[in] Tet  #Tet by 4 matrix of tetrahedral indices
@param[in] TriTag  #Tri vector of face tags
@param[in] TetTag  #Tet vector of tetrahedral tags
@throws std::runtime_error if file writing fails
)");
}

