#include "default_types.h"
#include <igl/is_vertex_manifold.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for is_vertex_manifold with overload handling
  auto is_vertex_manifold(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::Matrix<bool, Eigen::Dynamic, 1> B;
    igl::is_vertex_manifold(F, B);
    return B;
  }
}

// Bind the wrapper to the Python module
void bind_is_vertex_manifold(nb::module_ &m)
{
  m.def(
    "is_vertex_manifold",
    &pyigl::is_vertex_manifold,
    "F"_a,
R"(Check if a mesh is vertex-manifold.

This only checks whether the faces incident on each vertex form exactly one
connected component. Vertices incident on non-manifold edges are not consider
non-manifold by this function (see is_edge_manifold). Unreferenced verties are
considered non-manifold (zero components).

@param[in] F  #F by 3 list of triangle indices
@return B  #V list indicate whether each vertex is locally manifold (the mesh is vertex manifold if all(B) == True)");
}
