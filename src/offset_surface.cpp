#include "default_types.h"
#include <igl/offset_surface.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl {
  auto offset_surface(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const Numeric isolevel, 
    const Integer s,
    const igl::SignedDistanceType signed_distance_type) 
  {
    Eigen::MatrixXN SV;
    Eigen::MatrixXI SF;
    Eigen::MatrixXN GV;
  
    Eigen::VectorXI side;
    Eigen::MatrixXN so;
    igl::offset_surface(
      V, F, isolevel, s, signed_distance_type, SV, SF, GV, side,
      so);
  
    return std::make_tuple(SV, SF, GV, side, so);
  }
} // namespace pyigl

// Bind the wrapper to the Python module
void bind_offset_surface(nb::module_ &m) {
  m.def(
      "offset_surface", &pyigl::offset_surface, "V"_a, "F"_a, "isolevel"_a,
      "s"_a, "signed_distance_type"_a,
      R"(Compute a triangulated offset surface using matching cubes on a grid of signed distance values from the input triangle mesh.

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of mesh triangle indices into V
@param[in] isolevel  iso level to extract (signed distance: negative inside)
@param[in] s  number of grid cells along longest side (controls resolution)
@param[in] signed_distance_type  type of signing to use one of SIGNED_DISTANCE_TYPE_PSEUDONORMAL, SIGNED_DISTANCE_TYPE_WINDING_NUMBER, SIGNED_DISTANCE_TYPE_DEFAULT, SIGNED_DISTANCE_TYPE_UNSIGNED, SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER

@return Tuple containing:
   - SV: #SV by 3 list of output surface mesh vertex positions
   - SF: #SF by 3 list of output mesh triangle indices into SV
   - GV: #GV=side(0)*side(1)*side(2) by 3 list of grid cell centers
   - side: list of number of grid cells in x, y, and z directions
   - so: #GV by 3 list of signed distance values _near_ `isolevel` ('far' from `isolevel` these values are incorrect))");
}
