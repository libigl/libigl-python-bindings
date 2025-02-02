#include "default_types.h"
#include <igl/read_triangle_mesh.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto read_triangle_mesh(
    const std::filesystem::path & path)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    if(!igl::read_triangle_mesh(path.generic_string(),V,F))
    {
      // throw runtime exception
      throw std::runtime_error("Failed to read mesh from: " + path.generic_string());
    }
    return std::make_tuple(V,F);
  }
}

// Bind the wrapper to the Python module
void bind_read_triangle_mesh(nb::module_ &m)
{
  m.def(
    "read_triangle_mesh",
    &pyigl::read_triangle_mesh, 
    "filename"_a, 
R"(Read mesh from an ascii file with automatic detection of file format
among: mesh, msh obj, off, ply, stl, wrl.

@param[in] filename path to file
@param[out] V  double matrix #V by 3
@param[out] F  int matrix #F by 3
@return true iff success)"
    );
}



