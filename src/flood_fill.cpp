#include "default_types.h"
#include <igl/flood_fill.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto flood_fill(
    const nb::DRef<const Eigen::MatrixXI> &res,
    const nb::DRef<const Eigen::VectorXN> &S_in)
  {
    // flood_fill modifies S in place; copy in/out
    Eigen::VectorXN S = S_in;
    Eigen::VectorXI r = res.reshaped();
    igl::flood_fill(r, S);
    return S;
  }
}

void bind_flood_fill(nb::module_ &m)
{
  m.def("flood_fill", &pyigl::flood_fill, "res"_a, "S"_a,
    R"(Fill NaN values in a 3D grid via flood fill from non-NaN data.

@param[in] res  3-vector of grid dimensions [nx, ny, nz]
@param[in] S  res(0)*res(1)*res(2) list of scalar values with NaNs to fill
@return S  same array with NaNs filled)");
}
