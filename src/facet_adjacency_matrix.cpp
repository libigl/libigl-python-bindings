#include "default_types.h"
#include <igl/facet_adjacency_matrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for facet_adjacency_matrix with simplicial mesh (F)
  auto facet_adjacency_matrix(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixI A;
    igl::facet_adjacency_matrix(F, A);
    return A;
  }

}

// Bind the wrapper to the Python module
void bind_facet_adjacency_matrix(nb::module_ &m)
{
  m.def(
    "facet_adjacency_matrix",
    &pyigl::facet_adjacency_matrix,
    "F"_a,
R"(Construct a #F×#F adjacency matrix with A(i,j)>0 indicating that faces i and j
share an edge.

@param[in] F  #F by 3 list of facets
@param[out] A  #F by #F adjacency matrix)");
}
