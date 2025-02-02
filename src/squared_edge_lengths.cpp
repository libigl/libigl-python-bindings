#include "default_types.h"
#include <igl/squared_edge_lengths.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for squared_edge_lengths
  Eigen::MatrixXN squared_edge_lengths(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN L;
    igl::squared_edge_lengths(V, F, L);
    return L;
  }
}

// Bind the wrapper to the Python module
void bind_squared_edge_lengths(nb::module_ &m)
{
  m.def(
    "squared_edge_lengths",
    &pyigl::squared_edge_lengths,
    "V"_a,
    "F"_a,
R"(Constructs a list of squared lengths of edges opposite each index in a face (triangle/tet) list.

@param[in] V  #V by 3 eigen matrix of vertex positions
@param[in] F  #F by (2|3|4) list of mesh edges, triangles, or tets
@return L  #F by {1|3|6} matrix of squared edge lengths
    - For edges, a single column of lengths
    - For triangles, columns correspond to edges [1,2], [2,0], [0,1]
    - For tets, columns correspond to edges [3 0], [3 1], [3 2], [1 2], [2 0], [0 1])");
}
