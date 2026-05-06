#include "default_types.h"
#include <igl/is_boundary_edge.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Query specific edges
  auto is_boundary_edge_query(
    const nb::DRef<const Eigen::MatrixXI> &E,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // igl uses Eigen::MatrixXi (int32) internally — cast inputs
    Eigen::MatrixXi e = E.cast<int>(), f = F.cast<int>();
    Eigen::Array<bool, Eigen::Dynamic, 1> B;
    igl::is_boundary_edge(e, f, B);
    return B;
  }
  // Extract all boundary edges
  auto is_boundary_edge_extract(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // igl uses Eigen::MatrixXi (int32) internally — cast input and outputs
    Eigen::MatrixXi f = F.cast<int>();
    Eigen::Array<bool, Eigen::Dynamic, 1> B;
    Eigen::MatrixXi E_i;
    Eigen::VectorXi EMAP_i;
    igl::is_boundary_edge(f, B, E_i, EMAP_i);
    return std::make_tuple(B, Eigen::MatrixXI(E_i.cast<Integer>()), Eigen::VectorXI(EMAP_i.cast<Integer>()));
  }
}

void bind_is_boundary_edge(nb::module_ &m)
{
  m.def("is_boundary_edge", &pyigl::is_boundary_edge_query,
    "E"_a, "F"_a,
    R"(Determine for each edge in E if it is a boundary edge in F.

@param[in] E  #E by 2 list of edges to query
@param[in] F  #F by 3 list of triangles
@return B  #E list of bools, true iff edge is a boundary edge)");

  m.def("is_boundary_edge", &pyigl::is_boundary_edge_extract,
    "F"_a,
    R"(Determine boundary edges of mesh F.

@param[in] F  #F by 3 list of triangles
@return B  #uE list of bools, true iff unique edge is boundary
@return E  #uE by 2 list of unique edges
@return EMAP  #F*3 list of indices into E)");
}
