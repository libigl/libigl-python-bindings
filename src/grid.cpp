#include "default_types.h"
#include <igl/grid.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for igl::grid
  auto grid(const nb::DRef<const Eigen::VectorXI> &res)
  {
    Eigen::MatrixXN GV;
    igl::grid(res, GV);
    return GV;
  }
}

// Bind the wrapper to the Python module
void bind_grid(nb::module_ &m)
{
  m.def(
    "grid",
    &pyigl::grid,
    "res"_a,
R"(Construct vertices of a regular grid.

@param[in] res  Vector containing the number of vertices along each dimension
@return GV Matrix containing grid vertex positions suitable for input to igl::marching_cubes.)");
}
