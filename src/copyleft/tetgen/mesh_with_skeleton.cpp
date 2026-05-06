#include "default_types.h"
#include <igl/copyleft/tetgen/mesh_with_skeleton.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto mesh_with_skeleton(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::VectorXI> &P,
    const nb::DRef<const Eigen::MatrixXI> &BE,
    const nb::DRef<const Eigen::MatrixXI> &CE,
    const int samples_per_bone,
    const std::string &tetgen_flags)
  {
    // Non-template API uses MatrixXd/MatrixXi (col-major, int32)
    Eigen::MatrixXd Vd = V, Cd = C;
    Eigen::MatrixXi Fd = F.cast<int>(), BEd = BE.cast<int>(), CEd = CE.cast<int>();
    Eigen::VectorXi Pd = P.cast<int>();
    Eigen::MatrixXd VV;
    Eigen::MatrixXi TT, FF;
    if(!igl::copyleft::tetgen::mesh_with_skeleton(Vd, Fd, Cd, Pd, BEd, CEd,
        samples_per_bone, tetgen_flags, VV, TT, FF))
      throw std::runtime_error("mesh_with_skeleton: tetrahedralization failed");
    return std::make_tuple(Eigen::MatrixXN(VV), Eigen::MatrixXI(TT.cast<Integer>()),
      Eigen::MatrixXI(FF.cast<Integer>()));
  }
}

void bind_mesh_with_skeleton(nb::module_ &m)
{
  m.def("mesh_with_skeleton", &pyigl::mesh_with_skeleton,
    "V"_a, "F"_a, "C"_a,
    "P"_a = Eigen::VectorXI(),
    "BE"_a = Eigen::MatrixXI(),
    "CE"_a = Eigen::MatrixXI(),
    "samples_per_bone"_a = 10,
    "tetgen_flags"_a = "",
    R"(Mesh the interior of a surface with a graded tetrahedral mesh conforming to a skeleton.

@param[in] V  #V by 3 list of surface mesh vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] C  #C by 3 list of skeleton joint positions
@param[in] P  #P list of point handle indices into C (optional)
@param[in] BE #BE by 2 list of bone edge indices into C (optional)
@param[in] CE #CE by 2 list of cage edge indices into P (optional)
@param[in] samples_per_bone  number of samples added per bone (default: 10)
@param[in] tetgen_flags  tetgen option string (default: "" → "pq2Y")
@return tuple (VV, TT, FF):
  - VV  #VV by 3 tet-mesh vertex positions
  - TT  #TT by 4 tetrahedra indices
  - FF  #FF by 3 surface triangle indices
@raises RuntimeError on failure)");
}
