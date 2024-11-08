#include "default_types.h"
#include <igl/triangle_triangle_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  nb::object triangle_triangle_adjacency(
    const nb::DRef<const Eigen::MatrixXI> &F,
    bool return_TTi = false,
    bool use_lists = false)
  {
    if (use_lists)
    {
      std::vector<std::vector<std::vector<Integer>>> TT;
      
      if (return_TTi)
      {
        std::vector<std::vector<std::vector<Integer>>> TTi;
        igl::triangle_triangle_adjacency(F, true, TT, TTi);
        return nb::make_tuple(TT,TTi);
      }
      else
      {
        igl::triangle_triangle_adjacency(F, TT);
        return nb::cast(std::move(TT));
      }
    }
    else
    {
      Eigen::MatrixXI TT;
      
      if (return_TTi)
      {
        Eigen::MatrixXI TTi;
        igl::triangle_triangle_adjacency(F, TT, TTi);
        return nb::make_tuple(TT, TTi);
      }
      else
      {
        igl::triangle_triangle_adjacency(F, TT);
        return nb::cast(std::move(TT));
      }
    }
  }
}

// Bind the wrapper to the Python module
void bind_triangle_triangle_adjacency(nb::module_ &m)
{
  m.def(
    "triangle_triangle_adjacency",
    &pyigl::triangle_triangle_adjacency,
    "F"_a,
    "return_TTi"_a = false,
    "use_lists"_a = false,
R"(Constructs the triangle-triangle adjacency matrix for a given mesh (V,F).

@param[in] F  #F by 3 list of mesh faces (must be triangles)
@param[out] TT  #F by 3 adjacent matrix, where each element represents the id of the triangle adjacent to the corresponding edge
@param[out] TTi (if return_TTi=True) #F by 3 adjacent matrix, where each element represents the id of the edge of the adjacent triangle that shares an edge with the current triangle

- If `use_lists=True`, returns adjacency data as lists of lists for compatibility with non-manifold meshes.
)");
}
