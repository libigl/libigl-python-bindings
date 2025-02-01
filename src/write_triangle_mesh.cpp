#include "default_types.h"
#include <igl/write_triangle_mesh.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <limits>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void write_triangle_mesh(
    const std::filesystem::path & filename,
    const nb::DRef<const Eigen::MatrixXN> V,
    const nb::DRef<const Eigen::MatrixXI> F,
    const igl::FileEncoding encoding_enum)
  {
    // Throw an error if entries in F are bigger than can be cast to int32_t
    if(F.maxCoeff() > std::numeric_limits<std::int32_t>::max())
    {
      // throw runtime exception
      throw std::runtime_error("Entries in F are too big to be cast to int32_t (required by igl::write_triangle_mesh)");
    }
    Eigen::MatrixXi F32 = F.cast<std::int32_t>();
    if(!igl::write_triangle_mesh(filename.generic_string(),V,F32,encoding_enum))
    {
      // throw runtime exception
      throw std::runtime_error("Failed to write mesh to: " + filename.generic_string());
    }
  }
}

// Bind the wrapper to the Python module
void bind_write_triangle_mesh(nb::module_ &m)
{
  m.def(
    "write_triangle_mesh",
    &pyigl::write_triangle_mesh, 
    "filename"_a,
    "V"_a, 
    "F"_a, 
    "encoding"_a=igl::FileEncoding::Ascii,
R"(write mesh to a file with automatic detection of file format.  supported:
obj, off, stl, wrl, ply, mesh).

@tparam Scalar  type for positions and vectors (will be read as double and cast
           to Scalar)
@tparam Index  type for indices (will be read as int and cast to Index)
@param[in] str  path to file
@param[in] V  eigen double matrix #V by 3
@param[in] F  eigen int matrix #F by 3
@param[in] encoding  set file encoding (ascii or binary) when both are available)"
    );
}



