#include "default_types.h"
#include <igl/tri_tri_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Helper: DRef → RowVector3d (igl tri_tri uses RowVector3D=Matrix<Scalar,1,3> internally)
  // Reshaped has no .data(); copy to VectorXd first
  static Eigen::RowVector3d to3d(const nb::DRef<const Eigen::MatrixXN> &v) {
    const Eigen::VectorXd tmp = v.reshaped();
    return Eigen::RowVector3d(tmp.data());
  }

  // 3D overlap test only
  auto tri_tri_overlap_test_3d(
    const nb::DRef<const Eigen::MatrixXN> &p1,
    const nb::DRef<const Eigen::MatrixXN> &q1,
    const nb::DRef<const Eigen::MatrixXN> &r1,
    const nb::DRef<const Eigen::MatrixXN> &p2,
    const nb::DRef<const Eigen::MatrixXN> &q2,
    const nb::DRef<const Eigen::MatrixXN> &r2)
  {
    return igl::tri_tri_overlap_test_3d(
      to3d(p1), to3d(q1), to3d(r1), to3d(p2), to3d(q2), to3d(r2));
  }
  // 3D intersection test with segment
  auto tri_tri_intersection_test_3d(
    const nb::DRef<const Eigen::MatrixXN> &p1,
    const nb::DRef<const Eigen::MatrixXN> &q1,
    const nb::DRef<const Eigen::MatrixXN> &r1,
    const nb::DRef<const Eigen::MatrixXN> &p2,
    const nb::DRef<const Eigen::MatrixXN> &q2,
    const nb::DRef<const Eigen::MatrixXN> &r2)
  {
    bool coplanar;
    // tri_tri_intersection_test_3d uses RowVector3D=Matrix<Scalar,1,3> internally —
    // source/target must be row vectors
    Eigen::RowVector3d source, target;
    bool hit = igl::tri_tri_intersection_test_3d(
      to3d(p1), to3d(q1), to3d(r1), to3d(p2), to3d(q2), to3d(r2),
      coplanar, source, target);
    return std::make_tuple(hit, coplanar, Eigen::MatrixXN(source), Eigen::MatrixXN(target));
  }
}

void bind_tri_tri_intersect(nb::module_ &m)
{
  m.def("tri_tri_overlap_test_3d",
    &pyigl::tri_tri_overlap_test_3d,
    "p1"_a, "q1"_a, "r1"_a, "p2"_a, "q2"_a, "r2"_a,
    R"(Test if two 3D triangles overlap (including coplanar case).

@param[in] p1,q1,r1  vertices of first triangle
@param[in] p2,q2,r2  vertices of second triangle
@return true if triangles overlap)");

  m.def("tri_tri_intersection_test_3d",
    &pyigl::tri_tri_intersection_test_3d,
    "p1"_a, "q1"_a, "r1"_a, "p2"_a, "q2"_a, "r2"_a,
    R"(Test if two 3D triangles intersect; if so compute intersection segment.

@param[in] p1,q1,r1  vertices of first triangle
@param[in] p2,q2,r2  vertices of second triangle
@return hit  true if triangles intersect
@return coplanar  true if triangles are coplanar
@return source  first endpoint of intersection segment
@return target  second endpoint of intersection segment)");
}
