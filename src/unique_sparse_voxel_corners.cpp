#include "default_types.h"
#include <igl/unique_sparse_voxel_corners.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto unique_sparse_voxel_corners(
    const nb::DRef<const Eigen::VectorXN> &origin,
    const Numeric h0,
    const Integer depth,
    const nb::DRef<const Eigen::MatrixXI> &ijk)
  {
    Eigen::MatrixXI unique_ijk;
    Eigen::MatrixXI J;
    Eigen::MatrixXN unique_corners;
    
    igl::unique_sparse_voxel_corners(
      origin, h0, depth, ijk, unique_ijk, J, unique_corners);
    
    return std::make_tuple(unique_ijk, J, unique_corners);
  }
}

// Bind the wrapper to the Python module
void bind_unique_sparse_voxel_corners(nb::module_ &m)
{
  m.def(
    "unique_sparse_voxel_corners",
    &pyigl::unique_sparse_voxel_corners, 
    "origin"_a, 
    "h0"_a,
    "depth"_a,
    "ijk"_a,
    R"(
Give a list of octree cells subscripts (ijk) (minimum corners) at a given depth,
determine a unique list of subscripts to all incident corners of those
cells (de-replicating shared corners).

 @param[in] origin  3-vector of root cell minimum
 @param[in] h0   side length of current depth level
 @param[in] depth  current depth (single root cell is depth = 0)
 @param[in] ijk #ijk by 3 list of octree leaf cell minimum corner
   subscripts
 @param[out] unique_ijk #unique_ijk by 3 list of unique corner subscripts
 @param[out] J  #ijk by 8 list of indices into unique_ijk in yxz binary
   counting order
 @param[out] unique_corners #unique_ijk by 3 list of unique corner
   positions
    )");

}



