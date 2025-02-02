#include "default_types.h"
#include <igl/readOBJ.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readOBJ(const std::filesystem::path filename)
  {
    Eigen::MatrixXN V,TC,CN;
    Eigen::MatrixXI F,FTC,FN;
    if(!igl::readOBJ(filename.generic_string(),V,TC,CN,F,FTC,FN))
    {
      // throw runtime exception
      throw std::runtime_error("Failed to read mesh from: " + filename.generic_string());
    }
    return std::make_tuple(V,TC,CN,F,FTC,FN);
  }
}

// Bind the wrapper to the Python module
void bind_readOBJ(nb::module_ &m)
{
  m.def(
    "readOBJ",
    &pyigl::readOBJ, 
    "filename"_a, 
R"(
Read a mesh from an ascii obj file, filling in vertex positions, normals
and texture coordinates. Mesh may have faces of any number of degree

@param[in] str  path to .obj file
@param[out] V  double matrix of vertex positions  #V by 3
@param[out] TC  double matrix of texture coordinats #TC by 2
@param[out] N  double matrix of corner normals #N by 3
@param[out] F  #F list of face indices into vertex positions
@param[out] FTC  #F list of face indices into vertex texture coordinates
@param[out] FN  #F list of face indices into vertex normals)"
    );
}




