#include "default_types.h"
#include <igl/centroid.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto centroid(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXN c;
    Numeric vol;
    igl::centroid(V,F,c,vol);
    return std::make_tuple(c,vol);
  }
}

void bind_centroid(nb::module_ &m)
{
  m.def(
    "centroid",
    &pyigl::centroid,
    "V"_a,
    "F"_a,
R"(Computes the centroid and enclosed volume of a closed mesh using a surface
integral.

@param[in] V  #V by dim list of rest domain positions
@param[in] F  #F by 3 list of triangle indices into V
@return c    dim vector of centroid coordinates
@return vol  total volume of solid

\see moments
)");
}
