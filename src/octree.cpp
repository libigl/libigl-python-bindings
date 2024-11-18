#include "default_types.h"
#include <igl/octree.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto octree(const nb::DRef<const Eigen::MatrixXN> &P)
  {
    Eigen::MatrixXI CH;
    Eigen::MatrixXN CN;
    Eigen::VectorXN W;
    std::vector<std::vector<Integer>> point_indices;
    igl::octree(P,point_indices,CH,CN,W);
    return std::make_tuple(point_indices,CH,CN,W);
  }
}

// Bind the wrapper to the Python module
void bind_octree(nb::module_ &m)
{
  m.def(
    "octree",
    &pyigl::octree,
    "P"_a,
  R"(Given a set of 3D points P, generate data structures for a pointerless
octree. Each cell stores its points, children, center location and width.
Our octree is not dense. We use the following rule: if the current cell
has any number of points, it will have all 8 children. A leaf cell will
have -1's as its list of child indices.

We use a binary numbering of children. Treating the parent cell's center
as the origin, we number the octants in the following manner:
The first bit is 1 iff the octant's x coordinate is positive
The second bit is 1 iff the octant's y coordinate is positive
The third bit is 1 iff the octant's z coordinate is positive

For example, the octant with negative x, positive y, positive z is:
110 binary = 6 decimal

@param[in] P  #P by 3 list of point locations
@param[out] point_indices  a vector of vectors, where the ith entry is a
  vector of the indices into P that are the ith octree cell's points
@param[out] CH  #OctreeCells by 8, where the ith row is the indices of the
  ith octree cell's children
@param[out] CN  #OctreeCells by 3, where the ith row is a 3d row vector
  representing the position of the ith cell's center
@param[out] W  #OctreeCells, a vector where the ith entry is the width of
  the ith octree cell)"
);
}




