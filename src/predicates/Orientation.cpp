#include "default_types.h"
#include <igl/predicates/Orientation.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_Orientation(nb::module_ &m)
{
  nb::enum_<igl::predicates::Orientation>(m, "Orientation")
    .value("POSITIVE",    igl::predicates::Orientation::POSITIVE)
    .value("INSIDE",      igl::predicates::Orientation::INSIDE)
    .value("NEGATIVE",    igl::predicates::Orientation::NEGATIVE)
    .value("OUTSIDE",     igl::predicates::Orientation::OUTSIDE)
    .value("COLLINEAR",   igl::predicates::Orientation::COLLINEAR)
    .value("COPLANAR",    igl::predicates::Orientation::COPLANAR)
    .value("COCIRCULAR",  igl::predicates::Orientation::COCIRCULAR)
    .value("COSPHERICAL", igl::predicates::Orientation::COSPHERICAL)
    .value("DEGENERATE",  igl::predicates::Orientation::DEGENERATE)
    .export_values();
}
