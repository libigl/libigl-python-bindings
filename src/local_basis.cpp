#include "default_types.h"
#include <igl/local_basis.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto local_basis(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN B1, B2, B3;
    igl::local_basis(V, F, B1, B2, B3);
    return std::make_tuple(B1, B2, B3);
  }
}

// Bind the wrapper to the Python module
void bind_local_basis(nb::module_ &m)
{
  m.def(
    "local_basis",
    &pyigl::local_basis,
    "V"_a, 
    "F"_a,
    R"(Compute a local orthogonal reference system for each triangle in the given mesh.

    @param[in] V  #V by 3 eigen matrix of vertex positions
    @param[in] F  #F by 3 list of mesh faces (must be triangles)
    @param[out] B1 #F by 3 matrix of tangent vectors for each triangle
    @param[out] B2 #F by 3 matrix of tangent vectors perpendicular to B1 for each triangle
    @param[out] B3 #F by 3 matrix of normal vectors for each triangle
    )"
  );
}
