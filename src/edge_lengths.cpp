#include "default_types.h"
#include <igl/edge_lengths.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for edge_lengths function
  auto edge_lengths(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN L;
    igl::edge_lengths(V, F, L);
    return L;
  }
}

// Bind the wrapper to the Python module
void bind_edge_lengths(nb::module_ &m)
{
  m.def(
    "edge_lengths",
    &pyigl::edge_lengths,
    "V"_a, "F"_a,
R"(Constructs a list of lengths of edges opposite each index in a face
(triangle/tet) list.
  
@param[in] V  eigen matrix #V by 3
@param[in] F  #F by (2|3|4) list of mesh simplex indices into rows of V
@param[out] L  #F by {1|3|6} list of edge lengths 
    - For edges, column of lengths
    - For triangles, columns correspond to edges [1,2],[2,0],[0,1]
    - For tets, columns correspond to edges [3 0],[3 1],[3 2],[1 2],[2 0],[0 1])"
    );
}
