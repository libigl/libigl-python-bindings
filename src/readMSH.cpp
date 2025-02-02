#include "default_types.h"
#include <igl/readMSH.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readMSH(const std::filesystem::path& msh_file_name)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI Tri;
    Eigen::MatrixXI Tet;
    Eigen::VectorXI TriTag;
    Eigen::VectorXI TetTag;
    std::vector<std::string> XFields;
    std::vector<Eigen::MatrixXN> XF;
    std::vector<std::string> EFields;
    std::vector<Eigen::MatrixXN> TriF;
    std::vector<Eigen::MatrixXN> TetF;

    if (!igl::readMSH(msh_file_name.generic_string(), V, Tri, Tet, TriTag, TetTag, XFields, XF, EFields, TriF, TetF))
    {
      throw std::runtime_error("Failed to read .msh file: " + msh_file_name.generic_string());
    }

    return std::make_tuple(V, Tri, Tet, TriTag, TetTag, XFields, XF, EFields, TriF, TetF);
  }
}

// Bind the wrapper to the Python module
void bind_readMSH(nb::module_ &m)
{
  m.def(
    "readMSH",
    &pyigl::readMSH,
    "msh_file_name"_a,
R"(read triangle surface mesh and tetrahedral volume mesh from .msh file

@param[in] msh - file name
@param[out] X  eigen double matrix of vertex positions  #X by 3
@param[out] Tri  #Tri eigen integer matrix of triangular faces indices into vertex positions
@param[out] Tet  #Tet eigen integer matrix of tetrahedral indices into vertex positions
@param[out] TriTag #Tri eigen integer vector of tags associated with surface faces
@param[out] TetTag #Tet eigen integer vector of tags associated with volume elements
@param[out] XFields #XFields list of strings with field names associated with nodes
@param[out] XF      #XFields list of eigen double matrices, fields associated with nodes 
@param[out] EFields #EFields list of strings with field names associated with elements
@param[out] TriF    #EFields list of eigen double matrices, fields associated with surface elements
@param[out] TetF    #EFields list of eigen double matrices, fields associated with volume elements
@return true on success
\bug only version 2.2 of .msh file is supported (gmsh 3.X)
\bug only triangle surface elements and tetrahedral volumetric elements are supported
\bug only 3D information is supported
\bug only the 1st tag per element is returned (physical) 
\bug same element fields are expected to be associated with surface elements and volumetric elements
)");
}

