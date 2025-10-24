#include "default_types.h"
#include <igl/edges_to_path.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for the harmonic function
  auto harmonic(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &b,
    const nb::DRef<const Eigen::MatrixXN> &bc,
    const int k)
  {
    Eigen::MatrixXN W;
    if(!igl::harmonic(V, F, b, bc, k, W))
    {
      throw std::runtime_error("Failed to compute harmonic map");
    }
    #include "default_types.h"
    #include <igl/edges_to_path.h>
    #include <nanobind/nanobind.h>
    #include <nanobind/eigen/dense.h>
    #include <nanobind/stl/tuple.h>

    namespace nb = nanobind;
    using namespace nb::literals;

    namespace pyigl
    {
      // Wrapper for igl::edges_to_path
      auto edges_to_path(const nb::DRef<const Eigen::MatrixXI> &E)
      {
        Eigen::VectorXI I, J, K;
        igl::edges_to_path(E, I, J, K);
        return std::make_tuple(I, J, K);
      }
    }

// Bind the wrapper to the Python module
void bind_edges_to_path(nb::module_ &m)
{
    m.def(
    "edges_to_path",
    &pyigl::edges_to_path,
    "E"_a,
R"(Given a set of undirected, unique edges such that all form a
single connected component with exactly 0 or 2 nodes with valence = 1,
determine a path visiting all nodes.

Parameters
----------
E : (#E, 2) int array
    Undirected edges

Returns
-------
I : (#E+1,) int array
    Nodes in order tracing the chain (loop). If the output is a loop then I[0] == I[-1]
J : (#I-1,) int array
    Indices into E of edges tracing I
K : (#I-1,) int array in {0,1}
    Column indices so that I[i] == E[J[i], K[i]] for i < len(I)-1)"
    );
}
