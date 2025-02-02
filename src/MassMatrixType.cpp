#include "default_types.h"
#include <igl/massmatrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;


void bind_MassMatrixType(nb::module_ &m)
{
  nb::enum_<igl::MassMatrixType>(m, "MassMatrixType")
    .value("MASSMATRIX_TYPE_BARYCENTRIC", igl::MASSMATRIX_TYPE_BARYCENTRIC)
    .value("MASSMATRIX_TYPE_VORONOI", igl::MASSMATRIX_TYPE_VORONOI)
    .value("MASSMATRIX_TYPE_FULL", igl::MASSMATRIX_TYPE_FULL)
    .value("MASSMATRIX_TYPE_DEFAULT", igl::MASSMATRIX_TYPE_DEFAULT)
    .export_values()
    ;
}
