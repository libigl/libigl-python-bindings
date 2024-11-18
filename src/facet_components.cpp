#include "default_types.h"
#include <igl/facet_components.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for facet_components with simplicial mesh (F)
  auto facet_components(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI C;
    const int nc = igl::facet_components(F, C);
    return std::make_tuple(nc, C);
  }

}

// Bind the wrapper to the Python module
void bind_facet_components(nb::module_ &m)
{
  m.def(
    "facet_components",
    &pyigl::facet_components,
    "F"_a,
  R"(Compute connected components of facets based on edge-edge adjacency.

For connected components on vertices see igl::vertex_components

@param[in] F  #F by 3 list of triangle indices
@param[out] C  #F list of connected component ids
@return number of connected components)");
}
