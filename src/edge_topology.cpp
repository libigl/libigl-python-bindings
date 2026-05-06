#include "default_types.h"
#include <igl/edge_topology.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto edge_topology(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI EV, FE, EF;
    igl::edge_topology(V, F, EV, FE, EF);
    return std::make_tuple(EV, FE, EF);
  }
}

void bind_edge_topology(nb::module_ &m)
{
  m.def("edge_topology", &pyigl::edge_topology, "V"_a, "F"_a,
    R"(Initialize edges and their topological relations for an edge-manifold mesh.

@param[in] V  #V by dim list of vertex positions (unused, kept for API compatibility)
@param[in] F  #F by 3 list of triangle indices
@return EV  #E by 2 list of edge vertex indices
@return FE  #F by 3 list of face-edge relations (FE(f,c) is an edge incident on corner c of face f)
@return EF  #E by 2 list of edge-face relations (EF(e,:) are the two adjacent faces))");
}
