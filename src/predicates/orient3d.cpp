#include "default_types.h"
#include <igl/predicates/orient3d.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  igl::predicates::Orientation orient3d_scalar(
    const Eigen::Vector3d &pa,
    const Eigen::Vector3d &pb,
    const Eigen::Vector3d &pc,
    const Eigen::Vector3d &pd)
  {
    return igl::predicates::orient3d(pa, pb, pc, pd);
  }

  Eigen::VectorXi orient3d_vectorized(
    const Eigen::MatrixXN &A,
    const Eigen::MatrixXN &B,
    const Eigen::MatrixXN &C,
    const Eigen::MatrixXN &D)
  {
    Eigen::VectorXi R;
    igl::predicates::orient3d(A, B, C, D, R);
    return R;
  }
}

void bind_orient3d(nb::module_ &m)
{
  m.def(
    "orient3d",
    &pyigl::orient3d_scalar,
    "pa"_a, "pb"_a, "pc"_a, "pd"_a,
R"(Compute the orientation of the tetrahedron formed by pa, pb, pc, pd.

Uses exact arithmetic (Shewchuk predicates).

@param[in] pa  3D point
@param[in] pb  3D point
@param[in] pc  3D point
@param[in] pd  3D query point
@return POSITIVE if pd is below the plane oriented by pa,pb,pc,
  NEGATIVE if above, COPLANAR if on the plane.)");
  m.def(
    "orient3d",
    &pyigl::orient3d_vectorized,
    "A"_a, "B"_a, "C"_a, "D"_a,
R"(Vectorized orient3d: compute orientation for each row-tuple (A[i], B[i], C[i], D[i]).

@param[in] A  #P by 3 matrix of 3D points
@param[in] B  #P by 3 matrix of 3D points
@param[in] C  #P by 3 matrix of 3D points
@param[in] D  #P by 3 matrix of 3D points
@return #P vector of orientation values (+1, -1, or 0))");
}
