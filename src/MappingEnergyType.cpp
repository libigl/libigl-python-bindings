#include "default_types.h"
#include <igl/MappingEnergyType.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_MappingEnergyType(nb::module_ &m)
{
  nb::enum_<igl::MappingEnergyType>(m, "MappingEnergyType")
    .value("ARAP", igl::MappingEnergyType::ARAP)
    .value("LOG_ARAP", igl::MappingEnergyType::LOG_ARAP)
    .value("SYMMETRIC_DIRICHLET", igl::MappingEnergyType::SYMMETRIC_DIRICHLET)
    .value("CONFORMAL", igl::MappingEnergyType::CONFORMAL)
    .value("EXP_CONFORMAL", igl::MappingEnergyType::EXP_CONFORMAL)
    .value("EXP_SYMMETRIC_DIRICHLET", igl::MappingEnergyType::EXP_SYMMETRIC_DIRICHLET)
    .export_values()
    ;
}

