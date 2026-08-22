#include "default_types.h"
#include "parse_transforms.h"
#include <igl/swept_volume_bounding_box.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <Eigen/Geometry>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto swept_volume_bounding_box(
    const nb::DRef<const Eigen::MatrixXN> &V,
    /* Each transform is tiny; let nanobind copy them */
    const std::vector<Eigen::MatrixXN> &transforms)
  {
    const AffineN3List T =
      parse_transforms(transforms,"swept_volume_bounding_box");
    Eigen::AlignedBox<Numeric,3> box;
    igl::swept_volume_bounding_box(V,T,box);
    const Eigen::VectorXN min_corner = box.min();
    const Eigen::VectorXN max_corner = box.max();
    return std::make_tuple(min_corner,max_corner);
  }
}

// Bind the wrapper to the Python module
void bind_swept_volume_bounding_box(nb::module_ &m)
{
  m.def(
    "swept_volume_bounding_box",
    &pyigl::swept_volume_bounding_box,
    "V"_a,
    "transforms"_a,
R"(Construct an axis-aligned bounding box containing a shape undergoing a
motion sampled at a list of discrete rigid transformations.

@param[in] V  #V by 3 list of mesh positions in reference pose
@param[in] transforms  #transforms list of rigid transformations, one per time
    step, each given as a 4×4 (or 3×4) matrix
@return Tuple containing:
  - min_corner: 3-vector of the minimum corner of the box
  - max_corner: 3-vector of the maximum corner of the box)");
}
