#include "default_types.h"
#include <igl/false_barycentric_subdivision.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto false_barycentric_subdivision(
    const nb::DRef<const Eigen::MatrixXN>& V,
    const nb::DRef<const Eigen::MatrixXI>& F)
  {
    Eigen::MatrixXN VD;
    Eigen::MatrixXI FD;
    igl::false_barycentric_subdivision(V, F, VD, FD);
    return std::make_tuple(VD, FD);
  }
}

void bind_false_barycentric_subdivision(nb::module_ &m)
{
  m.def("false_barycentric_subdivision", &pyigl::false_barycentric_subdivision,
    "V"_a,
    "F"_a,
    R"(Refine the mesh by adding the barycenter of each face
@param[in] V       #V by 3 coordinates of the vertices
@param[in] F       #F by 3 list of mesh faces (must be triangles)
@param[out] VD      #V + #F by 3 coordinate of the vertices of the dual mesh
          The added vertices are added at the end of VD (should not be
          same references as (V,F)
@param[out] FD      #F*3 by 3 faces of the dual mesh)");
}
