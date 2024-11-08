#include "default_types.h"
#include <igl/is_edge_manifold.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for is_edge_manifold with overload handling
  nb::object is_edge_manifold(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const bool return_BF = false,
    const bool return_E = false,
    const bool return_EMAP = false,
    const bool return_BE = false)
  {
    bool result;
    Eigen::MatrixXI BF;
    Eigen::MatrixXI E;
    Eigen::VectorXI EMAP;
    Eigen::VectorX<bool> BE;

    result = igl::is_edge_manifold(F, BF, E, EMAP, BE);
    // 4 choose 4
    if (return_BF && return_E && return_EMAP && return_BE)
    {
      return nb::make_tuple(result, BF, E, EMAP, BE);
    }
    // 4 choose 3
    else if (return_BF && return_E && return_EMAP)
    {
      return nb::make_tuple(result, BF, E, EMAP);
    }
    else if (return_BF && return_E && return_BE)
    {
      return nb::make_tuple(result, BF, E, BE);
    }
    else if (return_BF && return_EMAP && return_BE)
    {
      return nb::make_tuple(result, BF, EMAP, BE);
    }
    else if (return_E && return_EMAP && return_BE)
    {
      return nb::make_tuple(result, E, EMAP, BE);
    }
    // 4 choose 2
    else if (return_BF && return_E)
    {
      return nb::make_tuple(result, BF, E);
    }
    else if (return_BF && return_EMAP)
    {
      return nb::make_tuple(result, BF, EMAP);
    }
    else if (return_BF && return_BE)
    {
      return nb::make_tuple(result, BF, BE);
    }
    else if (return_E && return_EMAP)
    {
      return nb::make_tuple(result, E, EMAP);
    }
    else if (return_E && return_BE)
    {
      return nb::make_tuple(result, E, BE);
    }
    else if (return_EMAP && return_BE)
    {
      return nb::make_tuple(result, EMAP, BE);
    }
    // 4 choose 1
    else if (return_BF)
    {
      return nb::make_tuple(result, BF);
    }else if (return_E)
    {
      return nb::make_tuple(result, E);
    }else if (return_EMAP)
    {
      return nb::make_tuple(result, EMAP);
    }else if (return_BE)
    {
      return nb::make_tuple(result, BE);
    }
    else
    {
      return nb::cast(result);
    }
  }
}

// Bind the wrapper to the Python module
void bind_is_edge_manifold(nb::module_ &m)
{
  m.def(
    "is_edge_manifold",
    &pyigl::is_edge_manifold,
    "F"_a,
    "return_BF"_a = false,
    "return_E"_a = false,
    "return_EMAP"_a = false,
    "return_BE"_a = false,
R"(Check if the mesh is edge-manifold (every edge is incident to one or two oppositely oriented faces).

@param[in] F  #F by 3 list of triangle indices
@param[out] BF  (if return_BF=True) #F by 3 list of flags for non-manifold edges opposite each vertex
@param[out] E   (if return_E=True)  #E by 2 list of unique edges
@param[out] EMAP (if return_EMAP=True) 3*#F list of indices of opposite edges in E
@param[out] BE  (if return_BE=True)  #E list of flags for whether each edge is non-manifold
@return True if all edges are manifold, otherwise False)");
}
