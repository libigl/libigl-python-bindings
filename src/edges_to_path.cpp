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
        // libigl's implementation internally maps to an int-backed buffer,
        // so ensure the input scalar type is 32-bit int to avoid Map pointer mismatches.
        using MatXI32 = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Options>;
        using VecXI32 = Eigen::Matrix<int, Eigen::Dynamic, 1>;

        MatXI32 Ei = E.template cast<int>();
        VecXI32 Ii, Ji, Ki;
        igl::edges_to_path(Ei, Ii, Ji, Ki);

        Eigen::VectorXI I = Ii.template cast<Integer>();
        Eigen::VectorXI J = Ji.template cast<Integer>();
        Eigen::VectorXI K = Ki.template cast<Integer>();
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
