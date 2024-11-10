#include "default_types.h"
#include <igl/connected_components.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for connected_components
  auto connected_components( const Eigen::SparseMatrix<Integer> &A)
  {
    Eigen::VectorXI C;
    Eigen::VectorXI K;
    Integer num_components = (Integer)igl::connected_components(A, C, K);
    return std::make_tuple(num_components, C, K);
  }
}

// Bind the wrapper to the Python module
void bind_connected_components(nb::module_ &m)
{
  m.def(
    "connected_components",
    &pyigl::connected_components,
    "A"_a,
R"(Determine the connected components of a graph described by the input adjacency matrix.

@param[in] A  #A by #A adjacency matrix (treated as describing a directed graph)
@param[out] C (if return_C=True) #A list of component indices in [0,#K-1]
@param[out] K (if return_K=True) #K list of sizes of each component
@return number of connected components)");
}
