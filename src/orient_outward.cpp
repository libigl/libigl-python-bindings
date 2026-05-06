#include "default_types.h"
#include <igl/orient_outward.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto orient_outward(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXI> &C)
  {
    // igl::orient_outward does &FF != &F pointer comparison — F must be plain MatrixXI
    // C is accessed with single-index C(f) — copy to VectorXI
    Eigen::MatrixXI f = F;
    Eigen::VectorXI c = C.reshaped();
    Eigen::MatrixXI FF;
    Eigen::VectorXI I;
    igl::orient_outward(V, f, c, FF, I);
    return std::make_tuple(FF, I);
  }
}

void bind_orient_outward(nb::module_ &m)
{
  m.def("orient_outward", &pyigl::orient_outward,
    "V"_a, "F"_a, "C"_a,
    R"(Orient each component of a mesh so normals point away from the centroid.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] C  #F list of component ids (from orientable_patches)
@return FF  #F by 3 list of reoriented triangle indices
@return I   max(C)+1 list of bools: true if face was flipped)");
}
