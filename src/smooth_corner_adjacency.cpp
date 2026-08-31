#include "default_types.h"
#include <igl/smooth_corner_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto smooth_corner_adjacency(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const Numeric corner_threshold_radians)
  {
    Eigen::VectorXI CI;
    Eigen::VectorXI CC;
    igl::smooth_corner_adjacency(V, F, corner_threshold_radians, CI, CC);
    return std::make_tuple(CI, CC);
  }
}

void bind_smooth_corner_adjacency(nb::module_ &m)
{
  m.def(
    "smooth_corner_adjacency",
    &pyigl::smooth_corner_adjacency,
    "V"_a,
    "F"_a,
    "corner_threshold_radians"_a,
R"(Determine the corner-to-face adjacency relationship that can be used for
computing crease-aware per-corner normals: two faces incident on a shared
vertex are grouped together for that corner only if their dihedral angle is
below the given threshold.

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of triangle indices into rows of V
@param[in] corner_threshold_radians  dihedral angle threshold in radians
@param[out] CI  flat list of face neighbors, indexed via CC (CSR-style)
@param[out] CC  #F*3+1 cumulative sum of corner-neighbor counts so that the
                neighbors of corner c are CI[CC[c]:CC[c+1]])");
}
