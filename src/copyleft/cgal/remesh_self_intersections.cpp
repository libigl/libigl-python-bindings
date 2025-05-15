#include "default_types.h"
#include <igl/copyleft/cgal/remesh_self_intersections.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // First overload: remesh_self_intersections with detailed outputs
  auto remesh_self_intersections(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const bool detect_only,
    const bool first_only,
    const bool stitch_all,
    const bool slow_and_more_precise_rounding,
    const int cutoff)
  {
    Eigen::MatrixXN VV;
    Eigen::MatrixXI FF;
    Eigen::MatrixXI IF;
    Eigen::VectorXI J;
    Eigen::VectorXI IM;

    igl::copyleft::cgal::RemeshSelfIntersectionsParam params(
      detect_only, first_only, stitch_all, slow_and_more_precise_rounding, cutoff);
    igl::copyleft::cgal::remesh_self_intersections(V, F, params, VV, FF, IF, J, IM);
    return std::make_tuple(VV, FF, IF, J, IM);
  }

}

// Bind the wrapper to the Python module
void bind_remesh_self_intersections(nb::module_ &m)
{
  // First overload
  m.def(
    "remesh_self_intersections",
    &pyigl::remesh_self_intersections,
    "V"_a,
    "F"_a,
    "detect_only"_a=false,
    "first_only"_a=false,
    "stitch_all"_a=false,
    "slow_and_more_precise_rounding"_a=false,
    "cutoff"_a=1000,
     // Simple overload binding
    R"(Resolve self-intersections in a mesh, without returning unique vertex indices (IM).

    @param[in] V  #V by 3 list of vertex positions
    @param[in] F  #F by 3 list of face indices
    @param[in] detect_only  only detect intersections, do not resolve
    @param[in] first_only  only return first intersection
    @param[in] stitch_all  stitch all intersections
    @param[in] slow_and_more_precise_rounding  use slow and more precise rounding
    @param[in] cutoff  maximum number of intersections to resolve
    @return Tuple containing:
      - VV: remeshed vertex positions
      - FF: remeshed face indices
      - IF: intersecting face pairs
      - J: birth triangle indices
      - IM if stitch_all = true   #VV list from 0 to #VV-1
           elseif stitch_all = false  #VV list of indices into VV of unique vertices.
      )");
}

