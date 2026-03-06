#include "default_types.h"
#include <igl/per_edge_normals.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto per_edge_normals(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::PerEdgeNormalsWeightingType weight)
  {
    Eigen::MatrixXN N;
    Eigen::MatrixXI E;
    Eigen::VectorXI EMAP;
    igl::per_edge_normals(V, F, weight, N, E, EMAP);
    return std::make_tuple(N, E, EMAP);
  }
}

void bind_per_edge_normals(nb::module_ &m)
{
  nb::enum_<igl::PerEdgeNormalsWeightingType>(m, "PerEdgeNormalsWeightingType")
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM",
      igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_UNIFORM)
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA",
      igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_AREA)
    .value("PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT",
      igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT)
    .export_values();

  m.def("per_edge_normals", &pyigl::per_edge_normals,
    "V"_a, "F"_a,
    "weight"_a = igl::PER_EDGE_NORMALS_WEIGHTING_TYPE_DEFAULT,
    R"(Compute per-edge normals for a triangle mesh.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] weight  weighting type (UNIFORM, AREA, or DEFAULT)
@return N  #E by 3 list of edge normals
@return E  #E by 2 list of edge vertex indices
@return EMAP  #F*3 list of indices from face-edges to E)");
}
