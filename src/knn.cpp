#include "default_types.h"
#include <igl/knn.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto knn(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const Integer k,
    const std::vector<std::vector<Integer>> &point_indices,
    const nb::DRef<const Eigen::MatrixXI> &CH,
    const nb::DRef<const Eigen::MatrixXN> &CN,
    const nb::DRef<const Eigen::VectorXN> &W)
  {
    Eigen::MatrixXI I;
    igl::knn(P,V,k,point_indices,CH,CN,W,I);
    return I;
  }
}

// Bind the wrapper to the Python module
void bind_knn(nb::module_ &m)
{
  m.def(
    "knn",
    &pyigl::knn,
    "P"_a,
    "V"_a,
    "k"_a,
    "point_indices"_a,
    "CH"_a,
    "CN"_a,
    "W"_a,
    R"(
Given a 3D set of points P, an whole number k, and an octree
find the indicies of the k nearest neighbors for each point in P.
Note that each point is its own neighbor.

The octree data structures used in this function are intended to be the
same ones output from igl::octree

@param[in] P  #P by 3 list of point locations
@param[in] V  #V by 3 list of point locations for which may be neighbors 
@param[in] k  number of neighbors to find
@param[in] point_indices  a vector of vectors, where the ith entry is a vector of
                          the indices into P that are the ith octree cell's points
@param[in] CH     #OctreeCells by 8, where the ith row is the indices of
                  the ith octree cell's children
@param[in] CN     #OctreeCells by 3, where the ith row is a 3d row vector
                  representing the position of the ith cell's center
@param[in] W      #OctreeCells, a vector where the ith entry is the width
         of the ith octree cell
@param[out] I  #P by k list of k-nearest-neighbor indices into V
)");
}
