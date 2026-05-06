#include "default_types.h"
#include <igl/mvc.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto mvc(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    // igl::mvc takes Eigen::MatrixXd (ColMajor) with non-const output ref
    Eigen::MatrixXd v = V, c = C;
    Eigen::MatrixXd W;
    igl::mvc(v, c, W);
    return Eigen::MatrixXN(W);
  }
}

void bind_mvc(nb::module_ &m)
{
  m.def("mvc", &pyigl::mvc, "V"_a, "C"_a,
    R"(Compute mean value coordinates for a polygon.

@param[in] V  #V by dim list of query point positions (dim=2 or 3)
@param[in] C  #C by dim list of polygon vertex positions in CCW order
@return W  #V by #C matrix of mean value coordinate weights)");
}
