#include "default_types.h"
#include <igl/cycodebase/box_cubic.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Bounding box of a single cubic Bézier curve.
  auto box_cubic_C(
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    Eigen::RowVectorXN B1, B2;
    igl::cycodebase::box_cubic(C, B1, B2);
    return std::make_tuple(B1, B2);
  }
  // Bounding boxes of many indexed cubic Bézier curves.
  auto box_cubic_PC(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &C)
  {
    Eigen::MatrixXN B1, B2;
    igl::cycodebase::box_cubic(P, C, B1, B2);
    return std::make_tuple(B1, B2);
  }
}

void bind_box_cubic(nb::module_ &m)
{
  m.def("box_cubic", &pyigl::box_cubic_C, "C"_a,
    R"(Compute the min/max box corners tightly containing a cubic Bézier curve.

@param[in] C  4 by dim matrix of control points defining the cubic Bézier curve
@return Tuple (B1, B2) where
  B1  1 by dim min corner of the bounding box
  B2  1 by dim max corner of the bounding box)");

  m.def("box_cubic", &pyigl::box_cubic_PC, "P"_a, "C"_a,
    R"(Compute bounding boxes for a collection of indexed cubic Bézier curves.

@param[in] P  #P by dim matrix of control point locations
@param[in] C  #C by 4 matrix of indices into P defining the cubics
@return Tuple (B1, B2) where
  B1  #C by dim matrix of min corners of the bounding boxes
  B2  #C by dim matrix of max corners of the bounding boxes)");
}
