#include "default_types.h"
#include <igl/copyleft/cgal/outer_hull.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto outer_hull(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // int32 required by libigl internals
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXN HV;
    Eigen::MatrixXi HF;
    Eigen::VectorXi J;
    Eigen::Matrix<bool, Eigen::Dynamic, 1> flip;
    igl::copyleft::cgal::outer_hull(V, Fi, HV, HF, J, flip);
    return std::make_tuple(HV,
      Eigen::MatrixXI(HF.cast<Integer>()),
      Eigen::VectorXI(J.cast<Integer>()),
      Eigen::VectorXB(flip));
  }
}

void bind_outer_hull(nb::module_ &m)
{
  m.def("outer_hull", &pyigl::outer_hull, "V"_a, "F"_a,
    R"(Compute the outer hull of a piecewise-constant winding number mesh.

@param[in] V   #V by 3 list of vertex positions
@param[in] F   #F by 3 list of triangle indices into V
@return tuple (HV, HF, J, flip):
  - HV    #HV by 3 output vertex positions
  - HF    #HF by 3 output triangle indices into HV
  - J     #HF list of indices into F (birth faces)
  - flip  #HF list of bools, true if facet was flipped)");
}
