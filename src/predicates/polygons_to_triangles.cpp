#include "default_types.h"
#include <igl/predicates/polygons_to_triangles.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  std::tuple<Eigen::MatrixXi, Eigen::VectorXI> polygons_to_triangles(
    const Eigen::MatrixXN &V,
    const Eigen::VectorXI &I,
    const Eigen::VectorXI &C)
  {
    Eigen::VectorXi I_int = I.cast<int>();
    Eigen::VectorXi C_int = C.cast<int>();
    Eigen::MatrixXi F;
    Eigen::VectorXi J;
    igl::predicates::polygons_to_triangles(V, I_int, C_int, F, J);
    Eigen::VectorXI J_out = J.cast<Integer>();
    return {F, J_out};
  }
}

void bind_polygons_to_triangles(nb::module_ &m)
{
  m.def(
    "polygons_to_triangles",
    &pyigl::polygons_to_triangles,
    "V"_a, "I"_a, "C"_a,
R"(Triangulate each polygon of a polygon mesh with a fan.

@param[in] V  #V by dim vertex positions (used for orientation in 3D)
@param[in] I  #I list of polygon corner indices into rows of V
@param[in] C  #polygons+1 cumulative polygon sizes (C[i+1]-C[i] = size of polygon i)
@return (F, J) where F is #F by 3 list of triangle indices and J is #F list of
  source polygon indices.)");
}
