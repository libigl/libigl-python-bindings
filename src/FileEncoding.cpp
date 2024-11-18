#include "default_types.h"
#include <igl/FileEncoding.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_FileEncoding(nb::module_ &m)
{
  nb::enum_<igl::FileEncoding>(m,"FileEncoding")
    .value("Ascii", igl::FileEncoding::Ascii)
    .value("Binary", igl::FileEncoding::Binary)
    .export_values();
}
