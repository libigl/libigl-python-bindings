#include "default_types.h"
#include <igl/unique_edge_map.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto unique_edge_map(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI E;
    Eigen::MatrixXI uE;
    Eigen::VectorXI EMAP;
    Eigen::VectorXI uEC, uEE;
    igl::unique_edge_map(F, E, uE, EMAP, uEC, uEE);
    return nb::make_tuple(E, uE, EMAP, uEC, uEE);
  }

  auto unique_edge_map_lists( const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI E;
    Eigen::MatrixXI uE;
    Eigen::VectorXI EMAP;
    std::vector<std::vector<Integer>> uE2E;
    igl::unique_edge_map(F, E, uE, EMAP, uE2E);
    return std::make_tuple(E, uE, EMAP, uE2E);
  }
}

// Bind the wrapper to the Python module
void bind_unique_edge_map(nb::module_ &m)
{
  m.def(
    "unique_edge_map",
    &pyigl::unique_edge_map, 
    "F"_a,
R"(Construct relationships between facet "half"-(or rather "viewed")-edges E
to unique edges of the mesh seen as a graph.

@param[in] F  #F by 3 list of simplices
@param[out] E  #F*3 by 2 list of all directed edges
@param[out] uE  #uE by 2 list of unique undirected edges
@param[out] EMAP #F*3 list of indices into uE, mapping each directed edge to a unique
  undirected edge so that uE(EMAP(f+#F*c)) is the unique edge
  corresponding to E.row(f+#F*c)
@param[out] uE2E  (if return_uE2E=True) #uE list of lists of indices into E of coexisting edges
)");
  m.def(
    "unique_edge_map_lists",
    &pyigl::unique_edge_map_lists, 
    "F"_a,
R"(Construct relationships between facet "half"-(or rather "viewed")-edges E
to unique edges of the mesh seen as a graph.

@param[in] F  #F by 3 list of simplices
@param[out] E  #F*3 by 2 list of all directed edges
@param[out] uE  #uE by 2 list of unique undirected edges
@param[out] EMAP #F*3 list of indices into uE, mapping each directed edge to a unique
  undirected edge so that uE(EMAP(f+#F*c)) is the unique edge
  corresponding to E.row(f+#F*c)
@param[out] uE2E  (if return_uE2E=True) #uE list of lists of indices into E of coexisting edges
)");
}
