#include "default_types.h"
#include <igl/lazy_cage.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Simple overload: {shortest edge, midpoint} decimation, the sigma metric, the
  // dense grid, and the signed-distance field. grid_size <= 0 picks a heuristic.
  auto lazy_cage(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int num_faces,
    const int grid_size)
  {
    const Eigen::MatrixXd Vd = V;
    const Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXd CV;
    Eigen::MatrixXi CF;
    double sigma;
    const bool success = igl::lazy_cage(Vd, Fi, num_faces, grid_size, CV, CF, sigma);
    return std::make_tuple(
      success, Eigen::MatrixXN(CV), Eigen::MatrixXI(CF.cast<Integer>()), sigma);
  }

  // Full overload exposing every knob.
  auto lazy_cage_full(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int num_faces,
    const int grid_size,
    const double max_sigma,
    const int num_iters,
    const bool use_qslim,
    const igl::LazyCageMetric metric,
    const igl::LazyCageGridMode grid_mode,
    const igl::LazyCageDistance distance)
  {
    const Eigen::MatrixXd Vd = V;
    const Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXd CV;
    Eigen::MatrixXi CF;
    double sigma;
    const bool success = igl::lazy_cage(
      Vd, Fi, num_faces, grid_size, max_sigma, num_iters, use_qslim,
      metric, grid_mode, distance, CV, CF, sigma);
    return std::make_tuple(
      success, Eigen::MatrixXN(CV), Eigen::MatrixXI(CF.cast<Integer>()), sigma);
  }
}

void bind_lazy_cage(nb::module_ &m)
{
  m.def(
    "lazy_cage_default_grid_size",
    &igl::lazy_cage_default_grid_size,
    "num_faces"_a,
R"(Heuristic isosurfacing grid resolution (cells across the largest side) for a
lazy cage with num_faces faces.

@param[in] num_faces  desired number of cage faces
@return grid resolution)");

  m.def(
    "lazy_cage",
    &pyigl::lazy_cage,
    "V"_a,
    "F"_a,
    "num_faces"_a,
    "grid_size"_a = 0,
R"(Compute a "lazy cage" enclosing a closed input mesh: offset the surface and
decimate it down to num_faces while it stays a valid cage (encloses the input,
free of self-intersections, and not intersecting the input surface).

Uses the default settings ({shortest edge, midpoint} decimation, the sigma
metric, the dense grid, and the signed-distance field).

@param[in] V  #V by 3 list of input vertex positions (closed, manifold)
@param[in] F  #F by 3 list of input triangle indices into V
@param[in] num_faces  desired number of faces in the cage
@param[in] grid_size  isosurfacing resolution (cells along the largest side);
    <= 0 uses lazy_cage_default_grid_size(num_faces)
@param[out] success  true if a valid cage with num_faces faces was found
@param[out] CV  #CV by 3 list of cage vertex positions
@param[out] CF  #CF by 3 list of cage triangle indices into CV
@param[out] sigma  the offset distance used to build the returned cage)");

  m.def(
    "lazy_cage",
    &pyigl::lazy_cage_full,
    "V"_a,
    "F"_a,
    "num_faces"_a,
    "grid_size"_a,
    "max_sigma"_a,
    "num_iters"_a = 12,
    "use_qslim"_a = false,
    "metric"_a = igl::LAZY_CAGE_METRIC_SIGMA,
    "grid_mode"_a = igl::LAZY_CAGE_GRID_DENSE,
    "distance"_a = igl::LAZY_CAGE_DISTANCE_SIGNED,
R"(Compute a "lazy cage" with full control over the offset-and-decimate search.

@param[in] V  #V by 3 list of input vertex positions (closed, manifold)
@param[in] F  #F by 3 list of input triangle indices into V
@param[in] num_faces  desired number of faces in the cage
@param[in] grid_size  isosurfacing resolution; <= 0 uses the heuristic
@param[in] max_sigma  upper bound on the searched offset distance
@param[in] num_iters  number of bisection iterations on sigma
@param[in] use_qslim  decimate with igl.qslim (quadric error) instead of
    {shortest edge, midpoint}
@param[in] metric  objective minimized when choosing sigma (LazyCageMetric)
@param[in] grid_mode  dense vs. sparse isosurface extraction (LazyCageGridMode)
@param[in] distance  signed vs. unsigned distance field (LazyCageDistance)
@param[out] success  true if a valid cage with num_faces faces was found
@param[out] CV  #CV by 3 list of cage vertex positions
@param[out] CF  #CF by 3 list of cage triangle indices into CV
@param[out] sigma  the offset distance used to build the returned cage)");
}
