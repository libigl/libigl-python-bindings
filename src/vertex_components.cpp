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
  // Binding for vertex_components with adjacency matrix and counts
  m.def(
    "vertex_components",
    &pyigl::vertex_components,
    "F"_a,
    R"(Compute the connected components of a graph using an adjacency matrix, returning component IDs and counts.

@param[in] F       Matrix of triangle indices
@return            Vector C of component IDs per vertex)");
}
