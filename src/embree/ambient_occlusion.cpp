#include "default_types.h"
#include <igl/embree/ambient_occlusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto ambient_occlusion(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const int num_samples)
  {
    Eigen::VectorXN S;
    igl::embree::ambient_occlusion(V,F,P,N,num_samples,S);
    return S;
  }
  auto ambient_occlusion_ei(
    const igl::embree::EmbreeIntersector & ei,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &N,
    const int num_samples)
  {
    Eigen::VectorXN S;
    igl::embree::ambient_occlusion(ei,P,N,num_samples,S);
    return S;
  }
}

// Bind the wrapper to the Python module
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
R"(Compute ambient occlusion per given point

@param[in] V  #V by 3 list of mesh vertex positiosn
@param[in] F  #F by 3 list of mesh triangle indices into rows of V
@param[in] P  #P by 3 list of origin points
@param[in] N  #P by 3 list of origin normals
@param[out] S  #P list of ambient occlusion values between 1 (fully occluded) and
     0 (not occluded)
)");
  m.def(
    "ambient_occlusion",
    &pyigl::ambient_occlusion_ei, 
    "ei"_a,
    "P"_a,
    "N"_a,
    "num_samples"_a,
R"(Compute ambient occlusion per given point

@param[in] ei  EmbreeIntersector containing (V,F)
@param[in] P  #P by 3 list of origin points
@param[in] N  #P by 3 list of origin normals
@param[out] S  #P list of ambient occlusion values between 1 (fully occluded) and
     0 (not occluded)
)");
}
