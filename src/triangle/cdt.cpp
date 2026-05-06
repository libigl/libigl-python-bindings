#include "default_types.h"
#include <igl/triangle/cdt.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cdt(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &E,
    const std::string &flags)
  {
    // int32 required by libigl triangle internals
    Eigen::MatrixXi Ei = E.cast<int>();
    Eigen::MatrixXN WV;
    Eigen::MatrixXi WF, WE;
    Eigen::VectorXi J;
    igl::triangle::cdt(V, Ei, flags, WV, WF, WE, J);
    return std::make_tuple(WV, Eigen::MatrixXI(WF.cast<Integer>()),
      Eigen::MatrixXI(WE.cast<Integer>()), Eigen::VectorXI(J.cast<Integer>()));
  }
}

void bind_cdt(nb::module_ &m)
{
  m.def("cdt", &pyigl::cdt, "V"_a, "E"_a, "flags"_a = "-c",
    R"(Constrained Delaunay triangulation of the convex hull of 2D points and segments.

Preprocesses input to remove duplicates before calling triangle. Unlike
triangulate(), this returns an adjusted edge list on the output.

@param[in] V  #V by 2 list of 2D vertex positions
@param[in] E  #E by 2 list of constraint edge indices into V
@param[in] flags  triangle option string; should contain "-c" unless segments
    already enclose all points (default: "-c")
@return tuple (WV, WF, WE, J):
  - WV  #WV by 2 background mesh vertex positions
  - WF  #WF by 3 background mesh triangle indices into WV
  - WE  #WE by 2 constraint edge indices into WV (may be smaller than E
        if degenerate constraints were removed)
  - J   #V list of indices into WF/WE for each original vertex in V)");
}
