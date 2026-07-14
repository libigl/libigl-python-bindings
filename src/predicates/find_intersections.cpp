#include "default_types.h"
#include <igl/predicates/find_intersections.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  std::tuple<bool, Eigen::MatrixXI, Eigen::MatrixXI> find_intersections(
    const Eigen::MatrixXN &V1,
    const Eigen::MatrixXI &F1,
    const Eigen::MatrixXN &V2,
    const Eigen::MatrixXI &F2,
    const bool first_only)
  {
    Eigen::MatrixXi IF;
    Eigen::Matrix<bool, Eigen::Dynamic, 1> CP_bool;
    Eigen::MatrixXi F1_int = F1.cast<int>();
    Eigen::MatrixXi F2_int = F2.cast<int>();
    bool found = igl::predicates::find_intersections(
      V1, F1_int, V2, F2_int, first_only, IF, CP_bool);
    Eigen::MatrixXI IF_out = IF.cast<Integer>();
    Eigen::MatrixXI CP_out = CP_bool.cast<Integer>();
    return {found, IF_out, CP_out};
  }
}

void bind_find_intersections(nb::module_ &m)
{
  m.def(
    "find_intersections",
    &pyigl::find_intersections,
    "V1"_a, "F1"_a, "V2"_a, "F2"_a, "first_only"_a = false,
R"(Find intersecting triangle pairs between two meshes.

Uses AABB tree and exact predicates.

@param[in] V1        #V1 by 3 vertex positions of first mesh
@param[in] F1        #F1 by 3 triangle indices of first mesh
@param[in] V2        #V2 by 3 vertex positions of second mesh
@param[in] F2        #F2 by 3 triangle indices of second mesh
@param[in] first_only  stop after finding the first intersection
@return (found, IF, CP) where found is true if any intersections exist,
  IF is #IF by 2 list of intersecting face index pairs (into F1, F2),
  CP is #IF list of whether each intersection is coplanar.)");
}
