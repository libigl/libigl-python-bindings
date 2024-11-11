#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <igl/gaussian_curvature.h>
#include "default_types.h"

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto gaussian_curvature(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXN K; // Curvature values for each vertex
    igl::gaussian_curvature(V, F, K);
    return K;
  }
}

// Bind the wrapper to the Python module
void bind_gaussian_curvature(nb::module_ &m)
{
  m.def(
    "gaussian_curvature",
    &pyigl::gaussian_curvature,
    "V"_a, 
    "F"_a,
R"(Compute discrete Gaussian curvature at each vertex of a 3D mesh.

@param[in] V  #V by 3 matrix of vertex positions
@param[in] F  #F by 3 matrix of face indices
@return K  #V vector of discrete Gaussian curvature values at each vertex)"
    );
}
