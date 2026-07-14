#include "default_types.h"
#include <igl/predicates/find_self_intersections.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  std::tuple<bool, Eigen::MatrixXI, Eigen::MatrixXI> find_self_intersections(
    const Eigen::MatrixXN &V,
    const Eigen::MatrixXI &F,
    const bool first_only)
  {
    Eigen::MatrixXi IF;
    Eigen::Matrix<bool, Eigen::Dynamic, 1> CP_bool;
    Eigen::MatrixXi F_int = F.cast<int>();
    bool found = igl::predicates::find_self_intersections(V, F_int, first_only, IF, CP_bool);
    Eigen::MatrixXI IF_out = IF.cast<Integer>();
    Eigen::MatrixXI CP_out = CP_bool.cast<Integer>();
    return {found, IF_out, CP_out};
  }
}

void bind_find_self_intersections(nb::module_ &m)
{
  m.def(
    "find_self_intersections",
    &pyigl::find_self_intersections,
    "V"_a, "F"_a, "first_only"_a = false,
R"(Find self-intersecting triangle pairs within a mesh.

Uses AABB tree and exact predicates.

@param[in] V         #V by 3 vertex positions
@param[in] F         #F by 3 triangle indices
@param[in] first_only  stop after finding the first intersection
@return (found, IF, CP) where found is true if any self-intersections exist,
  IF is #IF by 2 list of intersecting face index pairs,
  CP is #IF list of whether each intersection is coplanar.)");
}
