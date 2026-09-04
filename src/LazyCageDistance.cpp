#include "default_types.h"
#include <igl/lazy_cage.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_LazyCageDistance(nb::module_ &m)
{
  nb::enum_<igl::LazyCageDistance>(m, "LazyCageDistance")
    .value("LAZY_CAGE_DISTANCE_SIGNED", igl::LAZY_CAGE_DISTANCE_SIGNED)
    .value("LAZY_CAGE_DISTANCE_UNSIGNED", igl::LAZY_CAGE_DISTANCE_UNSIGNED)
    .value("NUM_LAZY_CAGE_DISTANCE", igl::NUM_LAZY_CAGE_DISTANCE)
    .export_values()
    ;
}
