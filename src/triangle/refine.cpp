#include "default_types.h"
#include <igl/triangle/refine.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto refine(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &E,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const std::string &flags)
  {
    Eigen::MatrixXN V2;
    Eigen::MatrixXI F2;
    igl::triangle::refine(V, E, F, flags, V2, F2);
    return std::make_tuple(V2, F2);
  }
}

void bind_refine(nb::module_ &m)
{
  m.def("refine", &pyigl::refine,
    "V"_a, "E"_a, "F"_a, "flags"_a = "q",
    R"(Refine an existing 2D triangulation.

@param[in] V  #V by 2 list of 2D vertex positions
@param[in] E  #E by 2 list of segment indices (constraint edges)
@param[in] F  #F by 3 list of triangle indices
@param[in] flags  triangle option string (default: "q" for quality refinement)
@return tuple (V2, F2):
  - V2  #V2 by 2 refined vertex positions
  - F2  #F2 by 3 refined triangle indices)");
}
