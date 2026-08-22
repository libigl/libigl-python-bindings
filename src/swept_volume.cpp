#include "default_types.h"
#include "parse_transforms.h"
#include <igl/swept_volume.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto swept_volume(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    /* Each transform is tiny; let nanobind copy them */
    const std::vector<Eigen::MatrixXN> &transforms,
    const igl::SignedDistanceType sign_type,
    const Integer grid_res,
    const Numeric isolevel)
  {
    const AffineN3List T = parse_transforms(transforms,"swept_volume");
    Eigen::MatrixXN SV;
    Eigen::MatrixXI SF;
    igl::swept_volume(V,F,T,sign_type,grid_res,isolevel,SV,SF);
    return std::make_tuple(SV,SF);
  }
}

// Bind the wrapper to the Python module
void bind_swept_volume(nb::module_ &m)
{
  m.def(
    "swept_volume",
    &pyigl::swept_volume,
    "V"_a,
    "F"_a,
    "transforms"_a,
    "sign_type"_a = igl::SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER,
    "grid_res"_a = 50,
    "isolevel"_a = 0,
R"(Compute the surface of the swept volume of a solid object with surface
(V,F) mesh under going rigid motion.

@param[in] V  #V by 3 list of mesh positions in reference pose
@param[in] F  #F by 3 list of mesh indices into rows of V
@param[in] transforms  #transforms list of rigid transformations, one per time
    step, each given as a 4×4 (or 3×4) matrix
@param[in] sign_type  method for computing distance _sign_
@param[in] grid_res  number of grid cells on the longest side containing the
    motion (enough cells to cover isolevel, plus one, will also be added on
    each side as padding)
@param[in] isolevel  distance level to be contoured as swept volume (in the
    same units as V)
@return Tuple containing:
  - SV: #SV by 3 list of mesh positions of the swept surface
  - SF: #SF by 3 list of mesh faces into rows of SV)");
}
