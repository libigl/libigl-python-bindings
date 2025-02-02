#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>
#include <igl/principal_curvature.h>
#include "default_types.h"

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto principal_curvature(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    unsigned radius = 5,
    bool useKring = true)
  {
    Eigen::MatrixXN PD1; // Maximal curvature directions
    Eigen::MatrixXN PD2; // Minimal curvature directions
    Eigen::VectorXN PV1; // Maximal curvature values
    Eigen::VectorXN PV2; // Minimal curvature values
    std::vector<int> bad_vertices; // Indices of bad vertices

    igl::principal_curvature(V, F, PD1, PD2, PV1, PV2, bad_vertices, radius, useKring);

    return std::make_tuple(PD1, PD2, PV1, PV2, bad_vertices);
  }
}

// Bind the wrapper to the Python module
void bind_principal_curvature(nb::module_ &m)
{
  m.def(
    "principal_curvature",
    &pyigl::principal_curvature,
    "V"_a,
    "F"_a,
    "radius"_a = 5,
    "useKring"_a = true,
R"(Compute principal curvature directions and magnitudes for each vertex in a 3D mesh.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices (triangular mesh)
@param[in] radius  controls the size of the neighborhood, where 1 corresponds to average edge length
@param[in] useKring  boolean to use Kring neighborhood instead of ball neighborhood
@return Tuple containing:
  - PD1: #V by 3 maximal curvature direction for each vertex
  - PD2: #V by 3 minimal curvature direction for each vertex
  - PV1: #V vector of maximal curvature values for each vertex
  - PV2: #V vector of minimal curvature values for each vertex
  - bad_vertices: list of indices of bad vertices, if any)"
    );
}
