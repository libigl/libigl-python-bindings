#include "default_types.h"
#include <igl/intrinsic_delaunay_triangulation.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto intrinsic_delaunay_triangulation(
    const nb::DRef<const Eigen::MatrixXN> &l_in,
    const nb::DRef<const Eigen::MatrixXI> &F_in)
  {
    Eigen::MatrixXN l;
    Eigen::MatrixXI F,E,uE;
    Eigen::VectorXI EMAP;
    std::vector<std::vector<Integer> > uE2E;
    igl::intrinsic_delaunay_triangulation(l_in,F_in,l,F,E,uE,EMAP,uE2E);
    return std::make_tuple(l,F,E,uE,EMAP,uE2E);
    
  }
}

// Bind the wrapper to the Python module
void bind_intrinsic_delaunay_triangulation(nb::module_ &m)
{
  m.def(
    "intrinsic_delaunay_triangulation",
    &pyigl::intrinsic_delaunay_triangulation, 
    "l"_a, 
    "F"_a,
R"(
INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
"intrinsic Delaunay". See "An algorithm for the construction of intrinsic
delaunay triangulations with applications to digital geometry processing"
[Fisher et al. 2007].

@param[in] l_in  #F_in by 3 list of edge lengths (see edge_lengths)
@param[in] F_in  #F_in by 3 list of face indices into some unspecified vertex list V
@param[out] l  #F by 3 list of edge lengths
@param[out] F  #F by 3 list of new face indices. Note: Combinatorially F may contain
    non-manifold edges, duplicate faces and self-loops (e.g., an edge [1,1]
    or a face [1,1,1]). However, the *intrinsic geometry* is still
    well-defined and correct. See [Fisher et al. 2007] Figure 3 and 2nd to
    last paragraph of 1st page. Since F may be "non-eddge-manifold" in the
    usual combinatorial sense, it may be useful to call the more verbose
    overload below if disentangling edges will be necessary later on.
    Calling unique_edge_map on this F will give a _different_ result than
    those outputs.
@param[out] E  #F*3 by 2 list of all directed edges, such that E.row(f+#F*c) is the
@param[out]   edge opposite F(f,c)
@param[out] uE  #uE by 2 list of unique undirected edges
@param[out] EMAP #F*3 list of indices into uE, mapping each directed edge to unique
@param[out]   undirected edge
@param[out] uE2E  #uE list of lists of indices into E of coexisting edges

\see unique_edge_map
)");
}
