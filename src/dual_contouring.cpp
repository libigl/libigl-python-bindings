#include "default_types.h"
#include <igl/dual_contouring.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/function.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto dual_contouring(
    const std::function<Numeric(const Eigen::Matrix<Numeric,1,3> &)> &f,
    const std::function<Eigen::Matrix<Numeric,1,3>(const Eigen::Matrix<Numeric,1,3> &)> &f_grad,
    /* Let these get copied if needed */
    const Eigen::Matrix<Numeric,1,3> &min_corner,
    const Eigen::Matrix<Numeric,1,3> &max_corner,
    const Integer nx,
    const Integer ny,
    const Integer nz,
    const bool constrained,
    const bool triangles,
    const bool root_finding)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI Q;
    igl::dual_contouring(f,f_grad,min_corner,max_corner,nx,ny,nz,constrained,triangles,root_finding,V,Q);
    return std::make_tuple(V,Q);
  }
}

// Bind the wrapper to the Python module
void bind_dual_contouring(nb::module_ &m)
{
// See https://github.com/libigl/libigl-python-bindings/issues/194
//  m.def(
//    "dual_contouring",
//    &pyigl::dual_contouring, 
//    "f"_a,
//    "f_grad"_a,
//    "min_corner"_a,
//    "max_corner"_a,
//    "nx"_a,
//    "ny"_a,
//    "nz"_a,
//    "constrained"_a = false,
//    "triangles"_a = false,
//    "root_finding"_a = false,
//    R"(Dual contouring to extract a pure quad mesh from differentiable implicit
//function using a dense grid.
//
//@param[in] f  function returning >0 outside, <0 inside and =0 on the surface
//@param[in] f_grad  function returning ∇f/‖∇f‖
//@param[in] min_corner  position of primal grid vertex at minimum corner
//@param[in] max_corner  position of primal grid vertex at maximum corner
//@param[in] nx  number of vertices on x side of primal grid
//@param[in] ny  number of vertices on y side of primal grid
//@param[in] nz  number of vertices on z side of primal grid
//@param[in] constrained  whether to force dual vertices to lie strictly inside
//    corresponding primal cell (prevents self-intersections at cost of
//    surface quality; marginally slower)
//@param[in] triangles  whether to output four triangles instead of one quad per
//    crossing edge (quad mesh usually looks fine)
//@param[in] root_finding  whether to use root finding to identify crossing point on
//    each edge (improves quality a lot at cost of performance). If false,
//    use linear interpolation.
//@param[out] V  #V by 3 list of outputs vertex positions
//@param[out] Q  #Q by 4 (or 3 if triangles=true) face indices into rows of V
//    )");
}



