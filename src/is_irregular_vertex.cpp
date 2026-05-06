#include "default_types.h"
#include <igl/is_irregular_vertex.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_is_irregular_vertex(nb::module_ &m)
{
  m.def("is_irregular_vertex",
    [](const nb::DRef<const Eigen::MatrixXI> &F) -> std::vector<bool> {
      return igl::is_irregular_vertex(F);
    },
    "F"_a,
    R"(Determine if each vertex is irregular (valence > 6 for triangles, > 4 for quads).
Boundary vertices are ignored.

@param[in] F  #F by 3[4] list of triangle[quad] indices
@return #V vector of bools, true if vertex is irregular)");
}
