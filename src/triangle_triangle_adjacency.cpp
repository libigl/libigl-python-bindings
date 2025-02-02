#include "default_types.h"
#include <igl/triangle_triangle_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto triangle_triangle_adjacency( const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI TT;
    Eigen::MatrixXI TTi;
    igl::triangle_triangle_adjacency(F, TT, TTi);
    return nb::make_tuple(TT, TTi);
  }
  auto triangle_triangle_adjacency_lists( const nb::DRef<const Eigen::MatrixXI> &F)
  {
    std::vector<std::vector<std::vector<Integer>>> TT;
    std::vector<std::vector<std::vector<Integer>>> TTi;
    igl::triangle_triangle_adjacency(F, true, TT, TTi);
    return std::make_tuple(TT,TTi);
  }
}

// Bind the wrapper to the Python module
void bind_triangle_triangle_adjacency(nb::module_ &m)
{
  m.def(
    "triangle_triangle_adjacency",
    &pyigl::triangle_triangle_adjacency,
    "F"_a,
R"(Constructs the triangle-triangle adjacency matrix for a given mesh (V,F).

@param[in] F  #F by 3 list of mesh faces (must be triangles)
@param[out] TT  #F by 3 adjacent matrix, where each element represents the id of the triangle adjacent to the corresponding edge
@param[out] TTi (if return_TTi=True) #F by 3 adjacent matrix, where each element represents the id of the edge of the adjacent triangle that shares an edge with the current triangle

- If `use_lists=True`, returns adjacency data as lists of lists for compatibility with non-manifold meshes.
)");
  m.def(
    "triangle_triangle_adjacency_lists",
    &pyigl::triangle_triangle_adjacency_lists,
    "F"_a,
R"(Constructs the triangle-triangle adjacency matrix for a given mesh (V,F).

@param[in] F  #F by 3 list of mesh faces (must be triangles)
@param[out] TT  #F by 3 adjacent matrix, where each element represents the id of the triangle adjacent to the corresponding edge
@param[out] TTi (if return_TTi=True) #F by 3 adjacent matrix, where each element represents the id of the edge of the adjacent triangle that shares an edge with the current triangle

- If `use_lists=True`, returns adjacency data as lists of lists for compatibility with non-manifold meshes.
)");
}
