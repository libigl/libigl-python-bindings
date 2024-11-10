#include "default_types.h"
#include <igl/is_edge_manifold.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for is_edge_manifold with overload handling
  auto is_edge_manifold(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    bool result;
    Eigen::MatrixXI BF;
    Eigen::MatrixXI E;
    Eigen::VectorXI EMAP;
    Eigen::VectorX<bool> BE;

    result = igl::is_edge_manifold(F, BF, E, EMAP, BE);
    return std::make_tuple(result, BF, E, EMAP, BE);
  }
}

// Bind the wrapper to the Python module
void bind_is_edge_manifold(nb::module_ &m)
{
  m.def(
    "is_edge_manifold",
    &pyigl::is_edge_manifold,
    "F"_a,
R"(Check if the mesh is edge-manifold (every edge is incident to one or two oppositely oriented faces).

@param[in] F  #F by 3 list of triangle indices
@param[out] BF  (if return_BF=True) #F by 3 list of flags for non-manifold edges opposite each vertex
@param[out] E   (if return_E=True)  #E by 2 list of unique edges
@param[out] EMAP (if return_EMAP=True) 3*#F list of indices of opposite edges in E
@param[out] BE  (if return_BE=True)  #E list of flags for whether each edge is non-manifold
@return True if all edges are manifold, otherwise False)");
}
