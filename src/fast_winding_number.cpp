#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <igl/fast_winding_number.h>
#include "default_types.h"

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto fast_winding_number(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &Q)
  {
    Eigen::VectorXN W; // Winding number values for each query point
    igl::fast_winding_number(V, F, Q, W);
    return W;
  }
}

// Bind the wrapper to the Python module
void bind_fast_winding_number(nb::module_ &m)
{
  m.def(
    "fast_winding_number",
    &pyigl::fast_winding_number,
    "V"_a,
    "F"_a,
    "Q"_a,
R"(Compute approximate winding number for each query point based on a triangle soup mesh.

@param[in] V  #V by 3 matrix of mesh vertex positions
@param[in] F  #F by 3 matrix of triangle indices
@param[in] Q  #Q by 3 matrix of query positions
@return W  #Q vector of winding number values for each query point)"
    );
}
