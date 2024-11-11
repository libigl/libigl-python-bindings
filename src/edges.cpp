#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <igl/edges.h>
#include "default_types.h"

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Binding for edges function with face-based input
  Eigen::MatrixXI edges_from_faces(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI E;
    igl::edges(F, E);
    return E;
  }

  // Binding for edges function with polygon corner indices
  Eigen::MatrixXI edges_from_polygons(
    const nb::DRef<const Eigen::VectorXI> &I, 
    const nb::DRef<const Eigen::VectorXI> &C)
  {
    Eigen::MatrixXI E;
    igl::edges(I, C, E);
    return E;
  }

  // Binding for edges function with adjacency matrix input
  Eigen::MatrixXI edges_from_adjacency(
    const Eigen::SparseMatrix<Integer> &A)
  {
    Eigen::MatrixXI E;
    igl::edges(A, E);
    return E;
  }
}

// Define bindings for each overload of the edges function
void bind_edges(nb::module_ &m)
{
  m.def(
    "edges",
    &pyigl::edges_from_faces,
    "F"_a,
    R"(Construct a list of unique edges from a given face matrix.

@param[in] F  #F by (3|4) matrix of mesh face indices
@return #E by 2 matrix of unique edges
)"
  );

  m.def(
    "edges",
    &pyigl::edges_from_polygons,
    "I"_a, "C"_a,
    R"(Construct a list of unique edges from a given list of polygon corner indices.

@param[in] I  Vectorized list of polygon corner indices
@param[in] C  #polygons+1 list of cumulative polygon sizes
@return #E by 2 matrix of unique edges
)"
  );

  m.def(
    "edges",
    &pyigl::edges_from_adjacency,  // Using double for adjacency matrix example
    "A"_a,
    R"(Construct a list of unique edges from a given adjacency matrix.

@param[in] A  #V by #V symmetric adjacency matrix
@return #E by 2 matrix of unique edges
)"
  );
}
