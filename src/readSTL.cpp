#include "default_types.h"
#include <igl/readSTL.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <cstdio>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readSTL(const std::string &filename)
  {
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
      throw std::runtime_error("Cannot open STL file: " + filename);
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    Eigen::MatrixXN N;
    bool ok = igl::readSTL(fp, V, F, N);
    // fp is closed by readSTL
    if (!ok)
      throw std::runtime_error("Failed to read STL file: " + filename);
    return std::make_tuple(V, F, N);
  }
}

void bind_readSTL(nb::module_ &m)
{
  m.def("readSTL", &pyigl::readSTL, "filename"_a,
    R"(Read a mesh from an ASCII or binary STL file.

Note: STL files may have duplicate vertices. Use remove_duplicate_vertices
to merge them.

@param[in] filename  path to .stl file
@return V  #F*3 by 3 list of vertex positions (one per triangle corner)
@return F  #F by 3 list of triangle indices into V
@return N  #F by 3 list of face normals)");
}
