#include "default_types.h"
#include <igl/adjacency_matrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for adjacency_matrix with simplicial mesh (F)
  auto adjacency_matrix(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixI A;
    igl::adjacency_matrix(F, A);
    return A;
  }

  // Wrapper for adjacency_matrix with polygonal mesh (I, C)
  auto adjacency_matrix_polygon(
    const nb::DRef<const Eigen::VectorXI> &I,
    const nb::DRef<const Eigen::VectorXI> &C)
  {
    Eigen::SparseMatrixI A;
    igl::adjacency_matrix(I, C, A);
    return A;
  }
}

// Bind the wrapper to the Python module
void bind_adjacency_matrix(nb::module_ &m)
{
  m.def(
    "adjacency_matrix",
    &pyigl::adjacency_matrix,
    "F"_a,
R"(Constructs the adjacency matrix for a simplicial mesh.

@param[in] F  #F by dim matrix of mesh simplices
@return A Sparse adjacency matrix of size max(F)+1 by max(F)+1)");

  m.def(
    "adjacency_matrix",
    &pyigl::adjacency_matrix_polygon,
    "I"_a,
    "C"_a,
R"(Constructs the adjacency matrix for a polygon mesh.

@param[in] I  Vectorized list of polygon corner indices into rows of some matrix V
@param[in] C  Cumulative polygon sizes such that C(i+1)-C(i) = size of the ith polygon
@return A Sparse adjacency matrix of size max(I)+1 by max(I)+1)");
}
