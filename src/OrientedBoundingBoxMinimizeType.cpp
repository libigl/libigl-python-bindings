#include "default_types.h"
#include <igl/oriented_bounding_box.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;


void bind_OrientedBoundingBoxMinimizeType(nb::module_ &m)
{
  nb::enum_<igl::OrientedBoundingBoxMinimizeType>(m, "OrientedBoundingBoxMinimizeType")
    .value("ORIENTED_BOUNDING_BOX_MINIMIZE_VOLUME", igl::ORIENTED_BOUNDING_BOX_MINIMIZE_VOLUME)
    .value("ORIENTED_BOUNDING_BOX_MINIMIZE_SURFACE_AREA", igl::ORIENTED_BOUNDING_BOX_MINIMIZE_SURFACE_AREA)
    .value("ORIENTED_BOUNDING_BOX_MINIMIZE_DIAGONAL_LENGTH", igl::ORIENTED_BOUNDING_BOX_MINIMIZE_DIAGONAL_LENGTH)
    .export_values()
    ;
}

