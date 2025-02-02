#include "default_types.h"
#include <igl/cotmatrix_intrinsic.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cotmatrix_intrinsic(
    const nb::DRef<const Eigen::MatrixXN> &l,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixN L;
    igl::cotmatrix_intrinsic(l,F,L);
    return L;
  }
}

// Bind the wrapper to the Python module
void bind_cotmatrix_intrinsic(nb::module_ &m)
{
  m.def(
    "cotmatrix_intrinsic",
    &pyigl::cotmatrix_intrinsic, 
    "l"_a, 
    "F"_a,
R"(
Constructs the cotangent stiffness matrix (discrete laplacian) for a given
mesh with faces F and edge lengths l.

@param[in] l  #F by 3 list of (half-)edge lengths
@param[in] F  #F by 3 list of face indices into some (not necessarily
    determined/embedable) list of vertex positions V. It is assumed #V ==
    F.maxCoeff()+1
@param[out] L  #V by #V sparse Laplacian matrix

\see cotmatrix, intrinsic_delaunay_cotmatrix)");
}
