#include "default_types.h"
#include <igl/remove_unreferenced.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto remove_unreferenced(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN NV;
    Eigen::MatrixXI NF;
    Eigen::VectorXI I,J;
    igl::remove_unreferenced(V, F, NV, NF, I, J);
    return std::make_tuple(NV, NF, I, J);
  }
}

// Bind the wrapper to the Python module
void bind_remove_unreferenced(nb::module_ &m)
{
  m.def(
    "remove_unreferenced",
    &pyigl::remove_unreferenced,
    "F"_a,
    "n"_a=0,
R"(Remove unreferenced vertices from V, updating F accordingly
@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by ss list of simplices (Values of -1 are quitely skipped)
@param[out] NF  #NF by ss list of simplices
@param[out] I   #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)
     and V(find(IM<=size(NV,1)),:) = NV
@param[out] J  #NV by 1 list, such that NV = V(J,:))");
}

