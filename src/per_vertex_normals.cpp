#include "default_types.h"
#include <igl/per_vertex_normals.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/string.h>
#include <stdexcept>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto per_vertex_normals(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::PerVertexNormalsWeightingType weight_enum)
  {
    Eigen::MatrixXN N;
    igl::per_vertex_normals(V, F, weight_enum, N);
    return N;
  }
  auto per_vertex_normals_FN(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::PerVertexNormalsWeightingType weight_enum,
    const nb::DRef<const Eigen::MatrixXN> &FN)
  {
    Eigen::MatrixXN N;
    igl::per_vertex_normals(V, F, weight_enum, FN, N);
    return N;
  }
}

// Bind the wrapper to the Python module
void bind_per_vertex_normals(nb::module_ &m)
{
  nb::enum_<igl::PerVertexNormalsWeightingType>(m, "PerVertexNormalsWeightingType")
    .value("PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM", igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM)
    .value("PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA", igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA)
    .value("PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE", igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE)
    .value("PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT", igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT)
    .export_values()
    ;
  m.def(
    "per_vertex_normals",
    &pyigl::per_vertex_normals,
    "V"_a,
    "F"_a,
    "weighting"_a = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT,
R"(Compute per-vertex normals with optional weighting and face normals.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices
@param[in] weighting Optional string for weighting type ("uniform", "area", "angle", or "default")
@return N  #V by 3 matrix of vertex normals)");
  m.def(
    "per_vertex_normals",
    &pyigl::per_vertex_normals_FN,
    "V"_a,
    "F"_a,
    "weighting"_a = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT,
    "FN"_a,
R"(Compute per-vertex normals with optional weighting and face normals.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices
@param[in] weighting Optional string for weighting type ("uniform", "area", "angle", or "default")
@param[in] FN Optional #F by 3 matrix of face normals
@return N  #V by 3 matrix of vertex normals)");
}
