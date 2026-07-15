#include "default_types.h"
#include <igl/ambient_occlusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

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
    igl::ambient_occlusion(V, F, P, N, num_samples, S);
    return S;
  }
}

void bind_ambient_occlusion(nb::module_ &m)
{
  m.def(
    "ambient_occlusion",
    &pyigl::ambient_occlusion,
    "V"_a, "F"_a, "P"_a, "N"_a, "num_samples"_a,
    R"(Compute ambient occlusion per point for a triangle mesh.

@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of mesh face indices into V
@param[in] P  #P by 3 list of query point positions
@param[in] N  #P by 3 list of query point normals
@param[in] num_samples  number of samples to use (e.g., 500)
@return S  #P list of ambient occlusion values in [0,1], where 1 is
           fully occluded and 0 is unoccluded)");
}
