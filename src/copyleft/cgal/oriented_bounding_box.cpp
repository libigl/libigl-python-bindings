#include "default_types.h"
#include <igl/copyleft/cgal/oriented_bounding_box.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto oriented_bounding_box(
    const nb::DRef<const Eigen::MatrixXN> &P)
  {
    Eigen::MatrixXN R;
    igl::copyleft::cgal::oriented_bounding_box(P, R);
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
    R"(Given a set of points compute the rotation transformation of them such
that their axis-aligned bounding box is as small as possible.

igl::oriented_bounding_box is often faster and better

  @param[in] P  #P by 3 list of point locations
  @param[out] R  rotation matrix
  )");

}


