#include "default_types.h"
#include <igl/voxel_grid.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

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
}
