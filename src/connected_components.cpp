#include "default_types.h"
#include <igl/connected_components.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for connected_components
  nb::object connected_components(
    const Eigen::SparseMatrix<Integer> &A,
    const bool return_C = false,
    const bool return_K = false)
  {
    int num_components;
    Eigen::VectorXI C;
    Eigen::VectorXI K;

    if (return_C && return_K)
    {
      num_components = igl::connected_components(A, C, K);
      return nb::make_tuple(num_components, C, K);
    }
    else if (return_C)
    {
      num_components = igl::connected_components(A, C, K);
      return nb::make_tuple(num_components, C);
    }
    else if (return_K)
    {
      num_components = igl::connected_components(A, C, K);
      return nb::make_tuple(num_components, K);
    }
    else
    {
      num_components = igl::connected_components(A, C, K);
      return nb::cast(num_components);
    }
  }
}

// Bind the wrapper to the Python module
void bind_connected_components(nb::module_ &m)
{
  m.def(
    "connected_components",
    &pyigl::connected_components,
    "A"_a,
    "return_C"_a = false,
    "return_K"_a = false,
R"(Determine the connected components of a graph described by the input adjacency matrix.

@param[in] A  #A by #A adjacency matrix (treated as describing a directed graph)
@param[out] C (if return_C=True) #A list of component indices in [0,#K-1]
@param[out] K (if return_K=True) #K list of sizes of each component
@return number of connected components)");
}
