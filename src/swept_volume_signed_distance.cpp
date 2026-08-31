#include "default_types.h"
#include "parse_transforms.h"
#include <igl/swept_volume_signed_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <limits>
#include <stdexcept>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto swept_volume_signed_distance(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    /* Each transform is tiny; let nanobind copy them */
    const std::vector<Eigen::MatrixXN> &transforms,
    const igl::SignedDistanceType sign_type,
    const nb::DRef<const Eigen::MatrixXN> &GV,
    const nb::DRef<const Eigen::VectorXI> &res,
    const Numeric h,
    const Numeric isolevel,
    const nb::DRef<const Eigen::VectorXN> &S0)
  {
    const AffineN3List T =
      parse_transforms(transforms,"swept_volume_signed_distance");
    if(res.size() != 3)
    {
      throw std::runtime_error(
        "swept_volume_signed_distance: res must be a 3-vector");
    }
    if(res(0)*res(1)*res(2) != GV.rows())
    {
      throw std::runtime_error(
        "swept_volume_signed_distance: res(0)*res(1)*res(2) must equal GV.rows()");
    }
    const Eigen::VectorXI r = res;
    Eigen::VectorXN S;
    if(S0.size() == 0)
    {
      igl::swept_volume_signed_distance(V,F,T,sign_type,GV,r,h,isolevel,S);
    }else
    {
      if(S0.size() != GV.rows())
      {
        throw std::runtime_error(
          "swept_volume_signed_distance: S0 must have GV.rows() entries");
      }
      igl::swept_volume_signed_distance(V,F,T,sign_type,GV,r,h,isolevel,S0,S);
    }
    return S;
  }
}

// Bind the wrapper to the Python module
void bind_swept_volume_signed_distance(nb::module_ &m)
{
  m.def(
    "swept_volume_signed_distance",
    &pyigl::swept_volume_signed_distance,
    "V"_a,
    "F"_a,
    "transforms"_a,
    "sign_type"_a = igl::SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER,
    "GV"_a,
    "res"_a,
    "h"_a,
    "isolevel"_a = std::numeric_limits<Numeric>::infinity(),
    "S0"_a = Eigen::VectorXN(),
R"(Compute the signed distance to a sweep surface of a mesh under-going a
rigid motion discretely sampled at a list of transformations at a grid.

@param[in] V  #V by 3 list of mesh positions in reference pose
@param[in] F  #F by 3 list of triangle indices [0,n)
@param[in] transforms  #transforms list of rigid transformations, one per time
    step, each given as a 4×4 (or 3×4) matrix
@param[in] sign_type  method for computing distance _sign_
@param[in] GV  #GV by 3 list of evaluation point grid positions
@param[in] res  3-long resolution of the GV grid
@param[in] h  edge-length of grid
@param[in] isolevel  isolevel to "focus" on; grid positions far enough away
    from isolevel (based on h) will get approximate values. Set
    isolevel=inf (the default) to get good values everywhere (slow and
    unnecessary if just trying to extract the isolevel-level set).
@param[in] S0  #GV list of initial values (the minimum with these is taken);
    empty (the default) to start from scratch
@return S  #GV list of signed distances)");
}
