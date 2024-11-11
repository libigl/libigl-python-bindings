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
  auto weight_enum_from_string(const std::string &weighting)
  {
    igl::PerVertexNormalsWeightingType weight_enum;
    if (weighting == "uniform")
    {
      weight_enum = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM;
    }
    else if (weighting == "area")
    {
      weight_enum = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA;
    }
    else if (weighting == "angle")
    {
      weight_enum = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE;
    }
    else if (weighting == "default")
    {
      weight_enum = igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_DEFAULT;
    }
    else
    {
      throw std::invalid_argument("Invalid weighting type: " + weighting);
    }
    return weight_enum;
  }

  auto per_vertex_normals(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const std::string &weighting)
  {
    auto weight_enum = weight_enum_from_string(weighting);
    Eigen::MatrixXN N;
    igl::per_vertex_normals(V, F, weight_enum, N);
    return N;
  }
  auto per_vertex_normals_FN(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const std::string &weighting,
    const nb::DRef<const Eigen::MatrixXN> &FN)
  {
    auto weight_enum = weight_enum_from_string(weighting);
    Eigen::MatrixXN N;
    igl::per_vertex_normals(V, F, weight_enum, FN, N);
    return N;
  }
}

// Bind the wrapper to the Python module
void bind_per_vertex_normals(nb::module_ &m)
{
  m.def(
    "per_vertex_normals",
    &pyigl::per_vertex_normals,
    "V"_a,
    "F"_a,
    "weighting"_a = "default",
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
    "weighting"_a = "default",
    "FN"_a,
R"(Compute per-vertex normals with optional weighting and face normals.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices
@param[in] weighting Optional string for weighting type ("uniform", "area", "angle", or "default")
@param[in] FN Optional #F by 3 matrix of face normals
@return N  #V by 3 matrix of vertex normals)");
}
