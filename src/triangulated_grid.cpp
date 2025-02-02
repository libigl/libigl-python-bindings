#include "default_types.h"
#include <igl/triangulated_grid.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto triangulated_grid(
    const int nx,
    const int ny)
  {
    Eigen::MatrixXN GV;
    Eigen::MatrixXI GF;
    igl::triangulated_grid(nx,ny, GV,GF);
    return std::make_tuple(GV,GF);
  }
}

// Bind the wrapper to the Python module
void bind_triangulated_grid(nb::module_ &m)
{
  m.def(
    "triangulated_grid",
    &pyigl::triangulated_grid, 
    "nx"_a, 
    "ny"_a,
R"(Create a regular grid of elements (only 2D supported, currently) Vertex
position order is compatible with `igl::grid`

@param[in] nx  number of vertices in the x direction
@param[in] ny  number of vertices in the y direction
@param[out] GV  nx*ny by 2 list of mesh vertex positions.
@param[out] GF  2*(nx-1)*(ny-1) by 3  list of triangle indices

\see grid, quad_grid)"
    );
}



