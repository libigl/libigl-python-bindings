#include "default_types.h"
#include <igl/rigid_alignment.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto rigid_alignment(
    const nb::DRef<const Eigen::MatrixXN> &X,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N)
  {
    // t is used as rowwise row vector in igl — use RowVectorXd (MaxRowsAtCompileTime==1)
    Eigen::MatrixXd R;
    Eigen::RowVectorXd t;
    igl::rigid_alignment(X, P, N, R, t);
    return std::make_tuple(Eigen::MatrixXN(R), Eigen::MatrixXN(t));
  }
}

void bind_rigid_alignment(nb::module_ &m)
{
  m.def("rigid_alignment", &pyigl::rigid_alignment,
    "X"_a, "P"_a, "N"_a,
    R"(Find rigid transformation (R,t) minimizing ‖(X*R+t-P)'N‖².

@param[in] X  #X by 3 list of query points
@param[in] P  #X by 3 list of corresponding (closest) points on target
@param[in] N  #X by 3 list of unit normals at each point in P
@return R  3 by 3 rotation matrix
@return t  1 by 3 translation vector)");
}
