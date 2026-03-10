#include "default_types.h"
#include <igl/per_corner_normals.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto per_corner_normals(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const Numeric corner_threshold_degrees)
  {
    Eigen::MatrixXN CN;
    igl::per_corner_normals(V, F, corner_threshold_degrees, CN);
    return CN;
  }
}

void bind_per_corner_normals(nb::module_ &m)
{
  m.def("per_corner_normals", &pyigl::per_corner_normals,
    "V"_a, "F"_a, "corner_threshold_degrees"_a = 20.0,
    R"(Compute per-corner normals by averaging incident face normals within a threshold angle.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] corner_threshold_degrees  dihedral angle threshold in degrees; faces
  with normals deviating more than this are not averaged together
@return CN  #F*3 by 3 list of corner normals; CN.row(3*f+c) is the normal at
  corner c of face f)");
}
