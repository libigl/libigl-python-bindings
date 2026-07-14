#include "default_types.h"
#include <igl/predicates/segment_segment_intersect.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool segment_segment_intersect(
    const Eigen::Vector2d &A,
    const Eigen::Vector2d &B,
    const Eigen::Vector2d &C,
    const Eigen::Vector2d &D)
  {
    return igl::predicates::segment_segment_intersect(A, B, C, D);
  }
}

void bind_segment_segment_intersect(nb::module_ &m)
{
  m.def(
    "segment_segment_intersect",
    &pyigl::segment_segment_intersect,
    "A"_a, "B"_a, "C"_a, "D"_a,
R"(Test whether two 2D segments intersect using exact orient2d predicates.

@param[in] A  1st endpoint of segment 1
@param[in] B  2nd endpoint of segment 1
@param[in] C  1st endpoint of segment 2
@param[in] D  2nd endpoint of segment 2
@return true if the segments intersect.)");
}
