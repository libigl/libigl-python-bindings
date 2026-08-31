#include "default_types.h"
#include <igl/connect_boundary_to_infinity.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto connect_boundary_to_infinity_F(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI FO;
    igl::connect_boundary_to_infinity(F, FO);
    return FO;
  }

  auto connect_boundary_to_infinity_VF(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN VO;
    Eigen::MatrixXI FO;
    igl::connect_boundary_to_infinity(V, F, VO, FO);
    return std::make_tuple(VO, FO);
  }
}

void bind_connect_boundary_to_infinity(nb::module_ &m)
{
  m.def(
    "connect_boundary_to_infinity",
    &pyigl::connect_boundary_to_infinity_F,
    "F"_a,
R"(Connect all boundary edges to a fictitious point at infinity, closing an
open mesh (the result is edge-manifold if the input was manifold).

@param[in] F  #F by 3 list of face indices into some V
@param[out] FO  #F+#O by 3 list of face indices into [V; inf], original F come
                first)");
  m.def(
    "connect_boundary_to_infinity",
    &pyigl::connect_boundary_to_infinity_VF,
    "V"_a,
    "F"_a,
R"(Connect all boundary edges to a fictitious point at infinity, also
returning the augmented vertex list.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of face indices into rows of V
@param[out] VO  #V+1 by 3 list of vertex positions; original V come first and
                the last row is (inf, inf, inf)
@param[out] FO  #F+#O by 3 list of face indices into rows of VO)");
}
