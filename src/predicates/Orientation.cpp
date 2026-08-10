#include "default_types.h"
#include <igl/Orientation.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_Orientation(nb::module_ &m)
{
  nb::enum_<igl::Orientation>(m, "Orientation")
    .value("POSITIVE",    igl::Orientation::POSITIVE)
    .value("INSIDE",      igl::Orientation::INSIDE)
    .value("NEGATIVE",    igl::Orientation::NEGATIVE)
    .value("OUTSIDE",     igl::Orientation::OUTSIDE)
    .value("COLLINEAR",   igl::Orientation::COLLINEAR)
    .value("COPLANAR",    igl::Orientation::COPLANAR)
    .value("COCIRCULAR",  igl::Orientation::COCIRCULAR)
    .value("COSPHERICAL", igl::Orientation::COSPHERICAL)
    .value("DEGENERATE",  igl::Orientation::DEGENERATE)
    .export_values();
}
