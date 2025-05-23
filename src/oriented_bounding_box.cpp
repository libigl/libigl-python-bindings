#include "default_types.h"
#include <igl/oriented_bounding_box.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto oriented_bounding_box(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const int n,
    const igl::OrientedBoundingBoxMinimizeType minimize_type)
  {
    Eigen::MatrixXN R;
    igl::oriented_bounding_box(P, n, minimize_type, R);
    return R;
  }
}

// Bind the wrapper to the Python module
void bind_oriented_bounding_box(nb::module_ &m)
{
  m.def(
    "oriented_bounding_box",
    &pyigl::oriented_bounding_box, 
    "P"_a,
    "n"_a=10000,
    "minimize_type"_a=igl::ORIENTED_BOUNDING_BOX_MINIMIZE_VOLUME,
R"(Given a set of points compute the rotation transformation of them such
that their axis-aligned bounding box is as small as possible.
  
Consider passing the points on the convex hull of original list of points.
  
   @param[in] P  #P by 3 list of point locations
   @param[in] n  number of rotations to try
   @param[in] minimize_type  which quantity to minimize
   @param[out] R  rotation matrix
  )");

}

