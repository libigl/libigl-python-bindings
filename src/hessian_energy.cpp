#include "default_types.h"
#include <igl/hessian_energy.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto hessian_energy(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixN QH;
    igl::hessian_energy(V,F,QH);
    return QH;
  }

}

// Bind the wrapper to the Python module
void bind_hessian_energy(nb::module_ &m)
{
  m.def(
    "hessian_energy",
    &pyigl::hessian_energy, 
    "V"_a, 
    "F"_a,
R"(Constructs the matrix for the Hessian energy for a given
mesh (V,F).

  @tparam DerivedV  derived type of eigen matrix for V (e.g. derived from
    MatrixXd)
  @tparam DerivedF  derived type of eigen matrix for F (e.g. derived from
    MatrixXi)
  @tparam Scalar  scalar type for eigen sparse matrix (e.g. double)
  @param[in] V  #V by dim list of mesh vertex positions
  @param[in] F  #F by simplex_size list of mesh elements (triangles or tetrahedra)
  @param[out] QH  #V by #V Hessian energy matrix, each row i corresponding to V(i,:))");

}