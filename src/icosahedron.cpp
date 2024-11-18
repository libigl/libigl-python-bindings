#include "default_types.h"
#include <igl/icosahedron.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto icosahedron()
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    igl::icosahedron(V,F);
    return std::make_tuple(V,F);
  }
}

// Bind the wrapper to the Python module
void bind_icosahedron(nb::module_ &m)
{
  m.def(
    "icosahedron",
    &pyigl::icosahedron, 
R"(
Construct a icosahedron with radius 1 centered at the origin

Outputs:
  V  #V by 3 list of vertex positions
  F  #F by 3 list of triangle indices into rows of V)");
}

