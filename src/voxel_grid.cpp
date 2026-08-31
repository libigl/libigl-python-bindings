#include "default_types.h"
#include <igl/voxel_grid.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <Eigen/Geometry>
#include <stdexcept>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto voxel_grid(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const Numeric offset,
    const int s,
    const int pad_count)
  {
    Eigen::MatrixXN GV;
    Eigen::VectorXI side;
    igl::voxel_grid(V, offset, s, pad_count, GV, side);
    return std::make_tuple(GV, side);
  }

  auto voxel_grid_box(
    const nb::DRef<const Eigen::VectorXN> &min_corner,
    const nb::DRef<const Eigen::VectorXN> &max_corner,
    const int s,
    const int pad_count)
  {
    if(min_corner.size() != 3 || max_corner.size() != 3)
    {
      throw std::runtime_error(
        "voxel_grid: min_corner and max_corner must be 3-vectors");
    }
    // Named locals: `AlignedBox box(Matrix(a),Matrix(b));` would parse as a
    // function declaration
    const Eigen::Matrix<Numeric,3,1> mn = min_corner;
    const Eigen::Matrix<Numeric,3,1> mx = max_corner;
    const Eigen::AlignedBox<Numeric,3> box(mn,mx);
    Eigen::MatrixXN GV;
    Eigen::VectorXI side;
    igl::voxel_grid(box, s, pad_count, GV, side);
    return std::make_tuple(GV, side);
  }
}

// Bind the wrappers to the Python module
void bind_voxel_grid(nb::module_ &m)
{
  m.def(
    "voxel_grid",
    &pyigl::voxel_grid,
    "V"_a,
    "offset"_a =0.0,
    "s"_a,
    "pad_count"_a=0,
    R"(Constructs a voxel grid with an offset applied to each cell center.

@param[in] V         Matrix of input vertices
@param[in] offset    Offset to add to each cell center
@param[in] s         Number of cell centers on the largest side
@param[in] pad_count Number of cells beyond the box
@return              Tuple (GV, side) where GV contains cell center positions and side defines grid dimensions)");
  m.def(
    "voxel_grid",
    &pyigl::voxel_grid_box,
    "min_corner"_a,
    "max_corner"_a,
    "s"_a,
    "pad_count"_a=0,
    R"(Construct the cell center positions of a regular voxel grid (lattice)
made of perfectly square voxels enclosing a given axis-aligned box.

@param[in] min_corner  3-vector of the minimum corner of the box to enclose
@param[in] max_corner  3-vector of the maximum corner of the box to enclose
@param[in] s           Number of cell centers on the largest side (including 2*pad_count)
@param[in] pad_count   Number of cells beyond the box
@return                Tuple (GV, side) where GV contains cell center positions and side defines grid dimensions)");
}
