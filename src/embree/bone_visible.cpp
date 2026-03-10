#include "default_types.h"
#include <igl/embree/bone_visible.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto bone_visible(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &s,
    const nb::DRef<const Eigen::VectorXN> &d)
  {
    // int32 required; s/d must be column vectors (VectorXd), not row vectors
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::Matrix<bool, Eigen::Dynamic, 1> flag;
    // Pass s and d as VectorXN (column vectors) — DerivedSD must be col vector
    igl::embree::bone_visible(V, Fi, s, d, flag);
    return Eigen::VectorXB(flag);
  }
}

void bind_bone_visible(nb::module_ &m)
{
  m.def("bone_visible", &pyigl::bone_visible,
    "V"_a, "F"_a, "s"_a, "d"_a,
    R"(Test which mesh vertices are visible to a bone segment.

A vertex v is "visible" if the line segment from its projection onto the
bone to v does not intersect the mesh (see Baran & Popovic 2007).

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] s  3-vector: bone start position
@param[in] d  3-vector: bone end position
@return flag  #V bool vector, true if vertex is visible to the bone)");
}
