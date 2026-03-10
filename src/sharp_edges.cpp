#include "default_types.h"
#include <igl/sharp_edges.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto sharp_edges(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const Numeric angle)
  {
    Eigen::MatrixXI SE;
    igl::sharp_edges(V, F, angle, SE);
    return SE;
  }
}

void bind_sharp_edges(nb::module_ &m)
{
  m.def("sharp_edges", &pyigl::sharp_edges,
    "V"_a, "F"_a, "angle"_a,
    R"(Compute sharp edges of a mesh given a dihedral angle threshold.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] angle  dihedral angle threshold in radians (e.g. igl.PI * 0.11)
@return SE  #SE by 2 list of sharp edge vertex indices)");
}
