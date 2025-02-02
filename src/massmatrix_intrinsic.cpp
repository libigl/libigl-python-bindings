#include "default_types.h"
#include <igl/massmatrix_intrinsic.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto massmatrix_intrinsic(
    const nb::DRef<const Eigen::MatrixXN> &l,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::MassMatrixType type)
  {
    Eigen::SparseMatrixN M;
    igl::massmatrix_intrinsic(l,F,type,M);
    return M;
  }
}

// Bind the wrapper to the Python module
void bind_massmatrix_intrinsic(nb::module_ &m)
{
  m.def(
    "massmatrix_intrinsic",
    &pyigl::massmatrix_intrinsic, 
    "l"_a, 
    "F"_a,
    "type"_a=igl::MASSMATRIX_TYPE_DEFAULT,
R"(
Constructs the mass matrix  for a given
mesh with faces F and edge lengths l.

@param[in] l  #F by 3 list of (half-)edge lengths
@param[in] F  #F by 3 list of face indices into some (not necessarily
    determined/embedable) list of vertex positions V. It is assumed #V ==
    F.maxCoeff()+1
@param[out] L  #V by #V sparse Laplacian matrix

\see massmatrix, intrinsic_delaunay_massmatrix)");
}
