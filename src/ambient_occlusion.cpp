#include "default_types.h"
#include <igl/ambient_occlusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Core (embree-free) ambient occlusion: builds an AABB over (V,F) and shoots
  // rays with libigl's own intersector, so it is available in every wheel
  // regardless of whether the embree module was built.
  auto ambient_occlusion(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const int num_samples)
  {
    Eigen::VectorXN S;
    igl::ambient_occlusion(V, F, P, N, num_samples, S);
    return S;
  }
}

void bind_ambient_occlusion(nb::module_ &m)
{
  m.def(
    "ambient_occlusion",
    &pyigl::ambient_occlusion,
    "V"_a,
    "F"_a,
    "P"_a,
    "N"_a,
    "num_samples"_a,
    R"(Compute ambient occlusion per given point for a mesh (V,F).

This is the embree-free implementation from igl::core; for the (typically
faster) embree-accelerated version see igl.embree.ambient_occlusion.

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of mesh triangle indices into rows of V
@param[in] P  #P by 3 list of origin points
@param[in] N  #P by 3 list of origin normals
@param[in] num_samples  number of rays to shoot per point (e.g. 1000)
@return S  #P list of ambient occlusion values between 1 (fully occluded) and
  0 (not occluded))");
}
