#include "default_types.h"
#include <igl/lazy_cage.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_LazyCageMetric(nb::module_ &m)
{
  nb::enum_<igl::LazyCageMetric>(m, "LazyCageMetric")
    .value("LAZY_CAGE_METRIC_SIGMA", igl::LAZY_CAGE_METRIC_SIGMA)
    .value("LAZY_CAGE_METRIC_VOLUME", igl::LAZY_CAGE_METRIC_VOLUME)
    .value("LAZY_CAGE_METRIC_SURFACE_AREA", igl::LAZY_CAGE_METRIC_SURFACE_AREA)
    .value("NUM_LAZY_CAGE_METRIC", igl::NUM_LAZY_CAGE_METRIC)
    .export_values()
    ;
}
