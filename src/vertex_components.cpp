#include "default_types.h"
#include <igl/vertex_components.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for vertex_components with face indices
  auto vertex_components(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI C;
    igl::vertex_components(F, C);
    return C;
  }
}

// Bind the wrappers to the Python module
void bind_vertex_components(nb::module_ &m)
{
  // Binding for vertex_components from a mesh's face list
  m.def(
    "vertex_components",
    &pyigl::vertex_components,
    "F"_a,
    R"(Compute the connected component ids of each vertex of a mesh given its faces.

@param[in] F  #F by 3 matrix of triangle (face) indices
@return       Vector C of per-vertex connected-component ids)");
}
