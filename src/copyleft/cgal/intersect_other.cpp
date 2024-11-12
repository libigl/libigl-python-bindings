#include "default_types.h"
#include <igl/copyleft/cgal/intersect_other.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // First overload: intersect_other with detailed outputs
  auto intersect_other(
    const nb::DRef<const Eigen::MatrixXN> &VA,
    const nb::DRef<const Eigen::MatrixXI> &FA,
    const nb::DRef<const Eigen::MatrixXN> &VB,
    const nb::DRef<const Eigen::MatrixXI> &FB,
    const bool detect_only,
    const bool first_only,
    const bool stitch_all,
    const bool slow_and_more_precise_rounding,
    const int cutoff)
  {
    Eigen::MatrixXI IF;
    Eigen::MatrixXN VVAB;
    Eigen::MatrixXI FFAB;
    Eigen::VectorXI JAB;
    Eigen::VectorXI IMAB;

    igl::copyleft::cgal::RemeshSelfIntersectionsParam params(
      detect_only, first_only, stitch_all, slow_and_more_precise_rounding, cutoff);
    const bool success = igl::copyleft::cgal::intersect_other(
      VA, FA, VB, FB, params, IF, VVAB, FFAB, JAB, IMAB);

    return std::make_tuple(IF, VVAB, FFAB, JAB, IMAB);
  }

}

// Bind the wrapper to the Python module
void bind_intersect_other(nb::module_ &m)
{
  // First overload
  m.def(
    "intersect_other",
    &pyigl::intersect_other,
    "VA"_a,
    "FA"_a,
    "VB"_a,
    "FB"_a,
    "detect_only"_a=false,
    "first_only"_a=false,
    "stitch_all"_a=false,
    "slow_and_more_precise_rounding"_a=false,
    "cutoff"_a=1000,
    R"(Detect intersecting faces between two triangle meshes, providing detailed output.

    @param[in] VA  #V by 3 list of vertices for first mesh
    @param[in] FA  #F by 3 list of faces for first mesh
    @param[in] VB  #V by 3 list of vertices for second mesh
    @param[in] FB  #F by 3 list of faces for second mesh
    @param[in] detect_only  only detect intersections, do not resolve
    @param[in] first_only  only return first intersection
    @param[in] stitch_all  stitch all intersections
    @param[in] slow_and_more_precise_rounding  use slow and more precise rounding
    @param[in] cutoff  maximum number of intersections to resolve
    @return Tuple containing:
      - success: bool indicating if the operation succeeded
      - IF: # intersecting face pairs
      - VVAB: list of intersection vertex positions
      - FFAB: list of triangle indices into VVAB
      - JAB: list of indices into [FA;FB] denoting the birth triangle
      - IMAB: indices stitching duplicates from intersections)");

}
