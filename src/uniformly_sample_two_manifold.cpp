#include "default_types.h"
#include <igl/uniformly_sample_two_manifold.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto uniformly_sample_two_manifold(
    const nb::DRef<const Eigen::MatrixXN> &W,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int k,
    const Numeric push)
  {
    // igl takes MatrixXd (ColMajor) and MatrixXi (int32 ColMajor) with non-const output ref
    Eigen::MatrixXd w = W;
    Eigen::MatrixXi f = F.cast<int>();
    Eigen::MatrixXd WS;
    igl::uniformly_sample_two_manifold(w, f, k, push, WS);
    return Eigen::MatrixXN(WS);
  }
}

void bind_uniformly_sample_two_manifold(nb::module_ &m)
{
  m.def("uniformly_sample_two_manifold",
    &pyigl::uniformly_sample_two_manifold,
    "W"_a, "F"_a, "k"_a, "push"_a = 0.0,
    R"(Sample a mesh uniformly using furthest-point relaxation in weight space.

@param[in] W  #W by dim positions of mesh in weight space
@param[in] F  #F by 3 triangle indices
@param[in] k  number of samples
@param[in] push  factor to push samples away from hypercube corners
@return WS  k by dim sample locations in weight space)");
}
