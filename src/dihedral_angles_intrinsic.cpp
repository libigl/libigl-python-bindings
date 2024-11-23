#include "default_types.h"
#include <igl/dihedral_angles_intrinsic.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto dihedral_angles_intrinsic(
    const nb::DRef<const Eigen::MatrixXN>& A,
    const nb::DRef<const Eigen::MatrixXN>& L)
  {
    Eigen::MatrixXN theta, cos_theta;
    igl::dihedral_angles_intrinsic(A, L, theta, cos_theta);
    return std::make_tuple(theta, cos_theta);

  }
}

void bind_dihedral_angles_intrinsic(nb::module_ &m)
{
  m.def("dihedral_angles_intrinsic", &pyigl::dihedral_angles_intrinsic,
    "A"_a,
    "L"_a,
    R"(Compute dihedral angles for all tets of a given tet mesh's intrinsics.
@param[in] V  #V by dim list of vertex positions
@param[in] T  #V by 4 list of tet indices
@param[out] theta  #T by 6 list of dihedral angles (in radians)
@param[out] cos_theta  #T by 6 list of cosine of dihedral angles (in radians))");
}

