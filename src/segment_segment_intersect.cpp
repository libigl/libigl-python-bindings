#include "default_types.h"
#include <igl/segment_segment_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto segment_segment_intersect(
    const nb::DRef<const Eigen::MatrixXN> &p,
    const nb::DRef<const Eigen::MatrixXN> &r,
    const nb::DRef<const Eigen::MatrixXN> &q,
    const nb::DRef<const Eigen::MatrixXN> &s,
    const double eps)
  {
    // igl uses .cross() which requires SizeAtCompileTime==3 — copy to Vector3d
    // Reshaped has no .data(); copy to VectorXd first
    const Eigen::VectorXd pt = p.reshaped(), rt = r.reshaped();
    const Eigen::VectorXd qt = q.reshaped(), st = s.reshaped();
    const Eigen::Vector3d pv(pt.data()), rv(rt.data());
    const Eigen::Vector3d qv(qt.data()), sv(st.data());
    double t, u;
    bool hit = igl::segment_segment_intersect(pv, rv, qv, sv, t, u, eps);
    return std::make_tuple(hit, t, u);
  }
}

void bind_segment_segment_intersect(nb::module_ &m)
{
  m.def("segment_segment_intersect",
    &pyigl::segment_segment_intersect,
    "p"_a, "r"_a, "q"_a, "s"_a, "eps"_a = 1e-6,
    R"(Determine whether two 3D line segments intersect.

Segment A: p + t*r, t in [0,1]
Segment B: q + u*s, u in [0,1]

@param[in] p  3-vector origin of segment A
@param[in] r  3-vector direction of segment A
@param[in] q  3-vector origin of segment B
@param[in] s  3-vector direction of segment B
@param[in] eps  precision
@return hit  true if segments intersect
@return t  parameter along A
@return u  parameter along B)");
}
