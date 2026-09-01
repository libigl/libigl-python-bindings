#include "default_types.h"
#include <igl/lazy_cage.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_LazyCageGridMode(nb::module_ &m)
{
  nb::enum_<igl::LazyCageGridMode>(m, "LazyCageGridMode")
    .value("LAZY_CAGE_GRID_DENSE", igl::LAZY_CAGE_GRID_DENSE)
    .value("LAZY_CAGE_GRID_SPARSE", igl::LAZY_CAGE_GRID_SPARSE)
    .value("NUM_LAZY_CAGE_GRID_MODE", igl::NUM_LAZY_CAGE_GRID_MODE)
    .export_values()
    ;
}
