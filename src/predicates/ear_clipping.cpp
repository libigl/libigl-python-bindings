#include "default_types.h"
#include <igl/predicates/ear_clipping.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  std::tuple<bool, Eigen::MatrixXi> ear_clipping(
    const Eigen::MatrixXN &P)
  {
    Eigen::MatrixXi eF;
    bool ok = igl::predicates::ear_clipping(P, eF);
    return {ok, eF};
  }

  std::tuple<Eigen::MatrixXi, Eigen::MatrixXI> ear_clipping_with_reserved(
    const Eigen::MatrixXN &P,
    const Eigen::MatrixXI &RT)
  {
    Eigen::MatrixXi eF;
    Eigen::VectorXi I;
    Eigen::VectorXi RT_int = RT.cast<int>();
    igl::predicates::ear_clipping(P, RT_int, eF, I);
    Eigen::MatrixXI I_out = I.cast<Integer>();
    return {eF, I_out};
  }
}

void bind_ear_clipping(nb::module_ &m)
{
  m.def(
    "ear_clipping",
    &pyigl::ear_clipping,
    "P"_a,
R"(Ear-clipping triangulation of a 2D polygon.

Reverses P if necessary so output orientation matches input.

@param[in] P  #P by 2 list of 2D polygon vertices (CCW for proper mesh)
@return (ok, eF) where ok is true if mesh is proper (input is a simple polygon)
  and eF is #eF by 3 list of triangle indices into P.)");
  m.def(
    "ear_clipping",
    &pyigl::ear_clipping_with_reserved,
    "P"_a, "RT"_a,
R"(Ear-clipping triangulation with reserved (non-clippable) vertices.

@param[in] P   #P by 2 list of 2D polygon vertices
@param[in] RT  #P list, vertices marked 1 are preserved (not clipped)
@return (eF, I) where eF is the clipped ears (original indices into P) and
  I maps indices of the remaining polygon to original P indices.)");
}
