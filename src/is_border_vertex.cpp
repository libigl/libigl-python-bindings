#include "default_types.h"
#include <igl/is_border_vertex.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for is_border_vertex
  std::vector<bool> is_border_vertex(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    return igl::is_border_vertex(F);
  }
}

// Bind the wrapper to the Python module
void bind_is_border_vertex(nb::module_ &m)
{
  m.def(
    "is_border_vertex",
    &pyigl::is_border_vertex,
    "F"_a,
R"(Determine vertices on the open boundary of a manifold mesh with triangle faces.

@param[in] F  #F by 3 list of triangle indices
@return #V vector of bools indicating if vertices are on the boundary)");
}
