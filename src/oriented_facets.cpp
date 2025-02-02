#include "default_types.h"
#include <igl/oriented_facets.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for oriented_facets
  Eigen::MatrixXI oriented_facets(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI E;
    igl::oriented_facets(F, E);
    return E;
  }
}

// Bind the wrapper to the Python module
void bind_oriented_facets(nb::module_ &m)
{
  m.def(
    "oriented_facets",
    &pyigl::oriented_facets,
    "F"_a,
R"(Determines all directed facets of a given set of simplicial elements.

@param[in] F  #F by simplex_size matrix of simplices
@return E  #E by (simplex_size-1) matrix of directed facets, such that each row in E
           represents a facet opposite to a vertex in F)");
}
