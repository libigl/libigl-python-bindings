#include "default_types.h"
#include <igl/accumarray.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto accumarray_V(
    const nb::DRef<const Eigen::MatrixXI> &S,
    const nb::DRef<const Eigen::MatrixXN> &V)
  {
    // Copy to compact column vectors so single-index (i) access works
    const Eigen::VectorXI s = S.reshaped();
    const Eigen::VectorXN v = V.reshaped();
    Eigen::VectorXN A;
    igl::accumarray(s, v, A);
    return A;
  }
  auto accumarray_val(
    const nb::DRef<const Eigen::MatrixXI> &S,
    const Numeric val)
  {
    const Eigen::VectorXI s = S.reshaped();
    Eigen::VectorXN A;
    igl::accumarray(s, val, A);
    return A;
  }
}

void bind_accumarray(nb::module_ &m)
{
  m.def("accumarray", &pyigl::accumarray_V, "S"_a, "V"_a,
    R"(Accumulate values V at subscripts S. Like MATLAB's accumarray.

@param[in] S  #S list of subscripts (integer indices)
@param[in] V  #S list of values
@return A  max(S)+1 list of accumulated (summed) values)");

  m.def("accumarray", &pyigl::accumarray_val, "S"_a, "val"_a,
    R"(Accumulate a constant value at subscripts S. Like MATLAB's accumarray.

@param[in] S  #S list of subscripts (integer indices)
@param[in] val  scalar value to accumulate at each subscript
@return A  max(S)+1 list of accumulated (summed) values)");
}
