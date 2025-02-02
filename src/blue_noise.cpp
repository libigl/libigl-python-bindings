#include "default_types.h"
#include <igl/blue_noise.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto blue_noise(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F,
    const Numeric r)
  {
    Eigen::MatrixXN B;
    Eigen::VectorXI FI;
    Eigen::MatrixXN P;
    igl::blue_noise(V, F, r, B, FI, P);
    return std::make_tuple(B, FI, P);
  }
}

void bind_blue_noise(nb::module_ &m)
{
  m.def("blue_noise", &pyigl::blue_noise,
    "V"_a,
    "F"_a,
    "r"_a,
    R"("Fast Poisson Disk Sampling in Arbitrary Dimensions" [Bridson 2007].
For very dense samplings this is faster than (up to 2x) cyCodeBase's
implementation of "Sample Elimination for Generating Poisson Disk Sample
Sets" [Yuksel 2015]. YMMV
@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of mesh triangle indices into rows of V
@param[in] r  Poisson disk radius (evaluated according to Euclidean distance on V)
@param[out] B  #P by 3 list of barycentric coordinates, ith row are coordinates of
              ith sampled point in face FI(i)
@param[out] FI  #P list of indices into F 
@param[out] P  #P by dim list of sample positions.
)");
}
