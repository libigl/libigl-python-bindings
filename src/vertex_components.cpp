#include "default_types.h"
#include <igl/vertex_components.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

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

  // Wrapper for vertex_components with adjacency matrix
  auto vertex_components_from_adjacency_matrix(
    const Eigen::SparseMatrixI &adjacency)
  {
    Eigen::VectorXI c;
    Eigen::VectorXI counts;
    igl::vertex_components(adjacency, c, counts);
    return std::make_tuple(c, counts);
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

  m.def(
    "vertex_components_from_adjacency_matrix",
    &pyigl::vertex_components_from_adjacency_matrix,
    "adjacency"_a,
    R"(Compute the connected components of a graph using an adjacency matrix, returning component IDs and counts.

  @param[in] adjacency  n by n sparse adjacency matrix
  @return A tuple (c, counts) where c is an array of component ids (starting with 0) and counts is a #components array of counts for each component)");
}