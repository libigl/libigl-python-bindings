#include "default_types.h"
#include <igl/spectra/lscm.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto lscm(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN UV;
    if(!igl::spectra::lscm(V, F, UV))
    {
      throw std::runtime_error("igl::spectra::lscm failed");
    }
    return UV;
  }
}

void bind_lscm(nb::module_ &m)
{
  m.def(
    "lscm",
    &pyigl::lscm,
    "V"_a, "F"_a,
R"(Compute a free-boundary least-squares conformal map parametrization using
spectral decomposition. Assumes the mesh is a single connected component
topologically equivalent to a disk.

Implements "Spectral Conformal Parameterization" [Mullen et al. 2008].

@param[in] V   #V by 3 list of mesh vertex positions
@param[in] F   #F by 3 list of mesh face indices (triangles)
@param[out] UV #V by 2 list of UV coordinates
@return UV coordinates)");
}
