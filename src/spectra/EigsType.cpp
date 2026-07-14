#include <igl/eigs.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;

void bind_EigsType(nb::module_ &m)
{
  nb::enum_<igl::EigsType>(m, "EigsType")
    .value("EIGS_TYPE_SM", igl::EigsType::EIGS_TYPE_SM)
    .value("EIGS_TYPE_LM", igl::EigsType::EIGS_TYPE_LM)
    .export_values();
}
