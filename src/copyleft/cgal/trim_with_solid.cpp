#include "default_types.h"
#include <igl/copyleft/cgal/trim_with_solid.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto trim_with_solid(
    const nb::DRef<const Eigen::MatrixXN> & VA,
    const nb::DRef<const Eigen::MatrixXI> & FA,
    const nb::DRef<const Eigen::MatrixXN> & VB,
    const nb::DRef<const Eigen::MatrixXI> & FB)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    Eigen::VectorXB D;
    Eigen::VectorXI J;
    igl::copyleft::cgal::trim_with_solid(VA, FA, VB, FB, V, F, D, J);
    return std::make_tuple(V, F, D, J);
  }
}

// Binding function for the Python module
void bind_trim_with_solid(nb::module_ &m)
{
  m.def(
    "trim_with_solid",
    &pyigl::trim_with_solid,
    "VA"_a, "FA"_a, "VB"_a, "FB"_a,
    R"(Trim a mesh with another solid mesh, determining which faces lie inside or outside.

    @param[in] VA Vertex positions of mesh A
    @param[in] FA Triangle indices of mesh A
    @param[in] VB Vertex positions of mesh B (solid)
    @param[in] FB Triangle indices of mesh B
    @param[out] V Output vertex positions
    @param[out] F Output triangle indices
    @param[out] D Boolean vector indicating if each face is inside B
    @param[out] J Indices into FA showing parent triangle)");
}
