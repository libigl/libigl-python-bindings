#include "default_types.h"
#include <igl/readOFF.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readOFF(const std::filesystem::path filename)
  {
    Eigen::MatrixXN V,N;
    Eigen::MatrixXI F;
    if(!igl::readOFF(filename.generic_string(),V,F,N))
    {
      // throw runtime exception
      throw std::runtime_error("Failed to read mesh from: " + filename.generic_string() );
    }
    return std::make_tuple(V,F,N);
  }
}

// Bind the wrapper to the Python module
void bind_readOFF(nb::module_ &m)
{
  m.def(
    "readOFF",
    &pyigl::readOFF, 
    "filename"_a, 
R"(Read mesh from an ascii .off file

@param[in] filename path to file
@param[out] V  double matrix #V by 3
@param[out] F  int matrix #F by 3
@param[out] N,C  double matrix #V by 3 normals or colors
@return true iff success)"
    );
}




