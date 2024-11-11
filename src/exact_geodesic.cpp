#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <Eigen/Core>
#include <igl/exact_geodesic.h>
#include "default_types.h"

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for the exact_geodesic function
  Eigen::VectorXN exact_geodesic(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &VS,
    const nb::DRef<const Eigen::VectorXI> &FS,
    const nb::DRef<const Eigen::VectorXI> &VT,
    const nb::DRef<const Eigen::VectorXI> &FT)
  {
    Eigen::VectorXN D;
    igl::exact_geodesic(V, F, VS, FS, VT, FT, D);
    return D;
  }
}

// Bind the wrapper to the Python module
void bind_exact_geodesic(nb::module_ &m)
{
  m.def(
    "exact_geodesic",
    &pyigl::exact_geodesic,
    "V"_a,
    "F"_a,
    "VS"_a=Eigen::VectorXI(),
    "FS"_a=Eigen::VectorXI(),
    "VT"_a=Eigen::VectorXI(),
    "FT"_a=Eigen::VectorXI(),
    R"(Exact geodesic algorithm for computing distances on a triangular mesh.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices
@param[in] VS #VS by 1 vector of source vertex indices
@param[in] FS #FS by 1 vector of source face indices
@param[in] VT #VT by 1 vector of target vertex indices
@param[in] FT #FT by 1 vector of target face indices
@param[out] D  #VT+#FT vector of geodesic distances from each target to the nearest source
)"
  );
}
