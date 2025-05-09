#include "default_types.h"
#include <igl/map_vertices_to_circle.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto map_vertices_to_circle(
      const Eigen::MatrixXd &V,
      const Eigen::VectorXi &bnd)
  {
    Eigen::MatrixXd UV;
    igl::map_vertices_to_circle(V, bnd, UV);
    return UV;
  }
}

void bind_map_vertices_to_circle(nb::module_ &m)
{
  m.def("map_vertices_to_circle", &pyigl::map_vertices_to_circle,
        "V"_a,
        "bnd"_a,
        R"(Map the vertices whose indices are in a given boundary loop (bnd) on the
unit circle with spacing proportional to the original boundary edge
lengths.
@param[in] V  #V by dim list of mesh vertex positions
@param[in] b  #W list of vertex ids
@param[out] UV   #W by 2 list of 2D position on the unit circle for the vertices in b)");
}
