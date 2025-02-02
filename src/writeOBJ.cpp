#include "default_types.h"
#include <igl/writeOBJ.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <limits>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void writeOBJ(
    const std::filesystem::path & filename,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &CN,
    const nb::DRef<const Eigen::MatrixXI> &FN,
    const nb::DRef<const Eigen::MatrixXN> &TC,
    const nb::DRef<const Eigen::MatrixXI> &FTC)
  {
    if(!igl::writeOBJ(filename.generic_string(),V,F,CN,FN,TC,FTC))
    {
      // throw runtime exception
      throw std::runtime_error("Failed to write mesh to: " + filename.generic_string());
    }
  }
}

// Bind the wrapper to the Python module
void bind_writeOBJ(nb::module_ &m)
{
  m.def(
    "writeOBJ",
    &pyigl::writeOBJ, 
    "filename"_a,
    "V"_a, 
    "F"_a, 
    "CN"_a = Eigen::MatrixXN(),
    "FN"_a = Eigen::MatrixXI(),
    "TC"_a = Eigen::MatrixXN(),
    "FTC"_a = Eigen::MatrixXI(),
R"(Write a mesh in an ascii obj file

@param[in] str  path to outputfile
@param[in] V  #V by 3 mesh vertex positions
@param[in] F  #F by 3|4 mesh indices into V
@param[in] CN #CN by 3 normal vectors
@param[in] FN  #F by 3|4 corner normal indices into CN
@param[in] TC  #TC by 2|3 texture coordinates
@param[in] FTC #F by 3|4 corner texture coord indices into TC
@return true on success, false on error

\bug Horrifyingly, this does not have the same order of parameters as
readOBJ.

\see readOBJ)"
    );
}



