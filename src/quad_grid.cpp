#include "default_types.h"
#include <igl/quad_grid.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto quad_grid(
    const int nx,
    const int ny)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI Q,E;
    igl::quad_grid(nx,ny, V, Q, E);
    return std::make_tuple(V,Q,E);
  }
}

// Bind the wrapper to the Python module
void bind_quad_grid(nb::module_ &m)
{
  m.def(
    "quad_grid",
    &pyigl::quad_grid, 
    "nx"_a, 
    "ny"_a,
R"(Create a regular quad quad_grid of elements (only 2D supported, currently) Vertex
position order is compatible with `igl::quad_grid`

@param[in] nx  number of vertices in the x direction
@param[in] ny  number of vertices in the y direction
@param[out] V  nx*ny by 2 list of vertex positions
@param[out] Q  (nx-1)*(ny-1) by 4 list of quad indices into V
@param[out] E  (nx-1)*ny+(ny-1)*nx by 2 list of undirected quad edge indices into V

\see quad_grid, triangulated_quad_grid)"
    );
}



