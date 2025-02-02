#include "default_types.h"
#include <igl/writePLY.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void writePLY(
    const std::filesystem::path & filename,
    const Eigen::MatrixXN & V,
    const Eigen::MatrixXI & F_,
    const Eigen::MatrixXI & E_,
    const Eigen::MatrixXN & N,
    const Eigen::MatrixXN & UV,
    const Eigen::MatrixXN & VD,
    const std::vector<std::string> & VDheader,
    const Eigen::MatrixXN & FD,
    const std::vector<std::string> & FDheader,
    const Eigen::MatrixXN & ED,
    const std::vector<std::string> & EDheader,
    const std::vector<std::string> & comments,
    const igl::FileEncoding encoding)
  {
    // tinyply doesn't support int64
    Eigen::MatrixXi F = F_.cast<int>();
    Eigen::MatrixXi E = E_.cast<int>();

    if(!igl::writePLY(
      filename.generic_string(),
      V,
      F,
      E,
      N,
      UV,
      VD,
      VDheader,
      FD,
      FDheader,
      ED,
      EDheader,
      comments,
      encoding
    ))
    {
      throw std::runtime_error("Error writing " + filename.generic_string());
    }
  }
}

// Bind the wrapper to the Python module
void bind_writePLY(nb::module_ &m)
{
  m.def(
    "writePLY",
    &pyigl::writePLY,
    "filename"_a,
    "V"_a = Eigen::MatrixXN(),
    "F"_a = Eigen::MatrixXI(),
    "E"_a = Eigen::MatrixXI(),
    "N"_a = Eigen::MatrixXN(),
    "UV"_a = Eigen::MatrixXN(),
    "VD"_a = Eigen::MatrixXN(),
    "VDheader"_a = std::vector<std::string>(),
    "FD"_a = Eigen::MatrixXN(),
    "FDheader"_a = std::vector<std::string>(),
    "ED"_a = Eigen::MatrixXN(),
    "EDheader"_a = std::vector<std::string>(),
    "comments"_a = std::vector<std::string>(),
    "encoding"_a = igl::FileEncoding::Binary,
    R"(Write a mesh to a .ply file.

 @tparam Derived from Eigen matrix parameters
 @param[in] ply_stream  ply file output stream
 @param[in] V  (#V,3) matrix of vertex positions
 @param[in] F  (#F,3) list of face indices into vertex positions
 @param[in] E  (#E,2) list of edge indices into vertex positions
 @param[in] N  (#V,3) list of normals
 @param[in] UV (#V,2) list of texture coordinates
 @param[in] VD (#V,*) additional vertex data
 @param[in] Vheader (#V) list of vertex data headers
 @param[in] FD (#F,*) additional face data
 @param[in] Fheader (#F) list of face data headers
 @param[in] ED (#E,*) additional edge data
 @param[in] Eheader (#E) list of edge data headers
 @param[in] comments (*) file comments
 @param[in] encoding - enum, to set binary or ascii file format
 )");

}

