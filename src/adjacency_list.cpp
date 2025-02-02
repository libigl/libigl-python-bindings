#include "default_types.h"
#include <igl/adjacency_list.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for the first overload of adjacency_list for triangle meshes
  auto adjacency_list(
    const nb::DRef<const Eigen::MatrixXI> &F,
    bool sorted)
  {
    std::vector<std::vector<Integer>> A;
    igl::adjacency_list(F, A, sorted);
    return A;
  }
}

// Bind the wrappers to the Python module
void bind_adjacency_list(nb::module_ &m)
{
  // Binding for triangle mesh adjacency_list
  m.def(
    "adjacency_list",
    &pyigl::adjacency_list,
    "F"_a,
    "sorted"_a = false,
    R"(Constructs the graph adjacency list for a given triangle mesh.

@param[in] F       #F by dim list of mesh faces
@param[in] sorted  Boolean flag to sort adjacency counter-clockwise
@return            List of adjacent vertices for each vertex)");

}
