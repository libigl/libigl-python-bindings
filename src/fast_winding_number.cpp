#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <igl/fast_winding_number.h>
#include "default_types.h"
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // ---- Triangle soup, one-shot ------------------------------------------
  auto fast_winding_number_mesh(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &Q)
  {
    Eigen::VectorXN W;
    igl::fast_winding_number(V, F, Q, W);
    return W;
  }

  // ---- Point cloud, one-shot --------------------------------------------
  auto fast_winding_number_points(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const nb::DRef<const Eigen::VectorXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const int expansion_order,
    const Numeric beta)
  {
    Eigen::VectorXN WN;
    igl::fast_winding_number(P, N, A, Q, expansion_order, beta, WN);
    return WN;
  }

  // ---- Point cloud, cache the octree expansion --------------------------
  auto fast_winding_number_precompute(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const nb::DRef<const Eigen::VectorXN> &A,
    const std::vector<std::vector<Integer>> &point_indices,
    const nb::DRef<const Eigen::MatrixXI> &CH,
    const int expansion_order)
  {
    Eigen::MatrixXN CM;
    Eigen::VectorXN R;
    Eigen::MatrixXN EC;
    igl::fast_winding_number(
      P, N, A, point_indices, CH, expansion_order, CM, R, EC);
    return std::make_tuple(CM, R, EC);
  }

  // ---- Point cloud, evaluate using cached octree expansion --------------
  auto fast_winding_number_points_cached(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const nb::DRef<const Eigen::VectorXN> &A,
    const std::vector<std::vector<Integer>> &point_indices,
    const nb::DRef<const Eigen::MatrixXI> &CH,
    const nb::DRef<const Eigen::MatrixXN> &CM,
    const nb::DRef<const Eigen::VectorXN> &R,
    const nb::DRef<const Eigen::MatrixXN> &EC,
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const Numeric beta)
  {
    Eigen::VectorXN WN;
    igl::fast_winding_number(
      P, N, A, point_indices, CH, CM, R, EC, Q, beta, WN);
    return WN;
  }

  // ---- Triangle soup, cached BVH for repeated queries -------------------
  void fwn_bvh_init(
    igl::FastWindingNumberBVH &bvh,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int order)
  {
    igl::fast_winding_number(V, F, order, bvh);
  }

  auto fwn_bvh_query(
    const igl::FastWindingNumberBVH &bvh,
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const Numeric accuracy_scale)
  {
    Eigen::VectorXN W;
    igl::fast_winding_number(bvh, (float)accuracy_scale, Q, W);
    return W;
  }
}

void bind_fast_winding_number(nb::module_ &m)
{
  m.def(
    "fast_winding_number",
    &pyigl::fast_winding_number_mesh,
    "V"_a, "F"_a, "Q"_a,
R"(Compute approximate winding number for each query point based on a triangle soup mesh.

@param[in] V  #V by 3 matrix of mesh vertex positions
@param[in] F  #F by 3 matrix of triangle indices
@param[in] Q  #Q by 3 matrix of query positions
@return W  #Q vector of winding number values for each query point)");

  m.def(
    "fast_winding_number",
    &pyigl::fast_winding_number_points,
    "P"_a, "N"_a, "A"_a, "Q"_a, "expansion_order"_a = 2, "beta"_a = 2.0,
R"(Compute approximate winding number for each query point based on an oriented point cloud.

@param[in] P  #P by 3 matrix of point locations
@param[in] N  #P by 3 matrix of point normals
@param[in] A  #P vector of point areas
@param[in] Q  #Q by 3 matrix of query positions
@param[in] expansion_order  Taylor series expansion order (1, 2, or 3)
@param[in] beta  Barnes-Hut accuracy term separating near from far field;
  larger is more accurate and slower (2 is recommended). beta <= 0 forces exact
  evaluation.
@return WN  #Q vector of winding number values for each query point)");

  m.def(
    "fast_winding_number_precompute",
    &pyigl::fast_winding_number_precompute,
    "P"_a, "N"_a, "A"_a, "point_indices"_a, "CH"_a, "expansion_order"_a = 2,
R"(Precompute the octree Taylor expansion for point-cloud fast winding number,
so many query sets can reuse it. Build the octree with igl.octree(P).

@param[in] P  #P by 3 matrix of point locations
@param[in] N  #P by 3 matrix of point normals
@param[in] A  #P vector of point areas
@param[in] point_indices  list of lists of point indices per octree cell (from igl.octree)
@param[in] CH  #cells by 8 matrix of octree children (from igl.octree)
@param[in] expansion_order  Taylor series expansion order (1, 2, or 3)
@return Tuple (CM, R, EC) where
  CM  #cells by 3 matrix of each cell's center of mass
  R   #cells vector of each cell's radius
  EC  #cells by #coefficients matrix of expansion coefficients)");

  m.def(
    "fast_winding_number",
    &pyigl::fast_winding_number_points_cached,
    "P"_a, "N"_a, "A"_a, "point_indices"_a, "CH"_a, "CM"_a, "R"_a, "EC"_a,
    "Q"_a, "beta"_a = 2.0,
R"(Evaluate point-cloud fast winding number using a precomputed octree expansion
(see fast_winding_number_precompute).

@param[in] P  #P by 3 matrix of point locations
@param[in] N  #P by 3 matrix of point normals
@param[in] A  #P vector of point areas
@param[in] point_indices  list of lists of point indices per octree cell
@param[in] CH  #cells by 8 matrix of octree children
@param[in] CM  #cells by 3 matrix of cell centers of mass
@param[in] R   #cells vector of cell radii
@param[in] EC  #cells by #coefficients matrix of expansion coefficients
@param[in] Q  #Q by 3 matrix of query positions
@param[in] beta  Barnes-Hut accuracy term (2 recommended; <= 0 forces exact)
@return WN  #Q vector of winding number values for each query point)");

  nb::class_<igl::FastWindingNumberBVH>(m, "FastWindingNumberBVH",
R"(Cached bounding-volume hierarchy for triangle-soup fast winding number,
enabling many query sets against the same mesh without rebuilding.

Construct empty, then call init(V, F). Query with winding_number(Q).)")
    .def(nb::init<>())
    .def("init", &pyigl::fwn_bvh_init, "V"_a, "F"_a, "order"_a = 2,
R"(Build the hierarchy for mesh (V, F).

@param[in] V  #V by 3 matrix of mesh vertex positions
@param[in] F  #F by 3 matrix of triangle indices
@param[in] order  Taylor series expansion order (e.g. 2))")
    .def("winding_number", &pyigl::fwn_bvh_query, "Q"_a, "accuracy_scale"_a = 2.0,
R"(Compute winding numbers at query points using the cached hierarchy.

@param[in] Q  #Q by 3 matrix of query positions
@param[in] accuracy_scale  accuracy parameter (e.g. 2)
@return W  #Q vector of winding number values for each query point)");
}
