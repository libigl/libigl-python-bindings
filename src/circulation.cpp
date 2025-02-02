#include "default_types.h"
#include <igl/circulation.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto circulation(
    const int e,
    const bool ccw,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &EMAP,
    const nb::DRef<const Eigen::MatrixXI> &EF,
    const nb::DRef<const Eigen::MatrixXI> &EI)
  {
    std::vector<int> Nv, Nf;
    igl::circulation(e, ccw, F, EMAP, EF, EI, Nv, Nf);
    return std::make_tuple(Nv, Nf);
  }
}

// Bind the wrapper to the Python module
void bind_circulation(nb::module_ &m)
{
  m.def(
    "circulation",
    &pyigl::circulation,
    "e"_a,
    "ccw"_a,
    "F"_a,
    "EMAP"_a,
    "EF"_a,
    "EI"_a,
    R"(Return lists of "next" vertex indices (Nv) and face indices (Nf) for circulation.

    @param[in] e  index of edge to circulate
    @param[in] ccw  circulate in ccw direction
    @param[in] F  #F by 3 list of mesh faces
    @param[in] EMAP #F*3 list of indices mapping each directed edge to a unique edge in E
    @param[in] EF  #E by 2 list of edge flaps
    @param[in] EI  #E by 2 list of edge flap corners
    @return Tuple containing Nv (next vertex indices) and Nf (face indices))"
  );
}
