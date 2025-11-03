#include "default_types.h"
#include <igl/hessian.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto hessian(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixN H;
    igl::hessian(V,F,H);
    return H;
  }

}

// Bind the wrapper to the Python module
void bind_hessian(nb::module_ &m)
{
  m.def(
    "hessian",
    &pyigl::hessian, 
    "V"_a, 
    "F"_a,
R"(Constructs the finite element Hessian matrix
   as described in https://arxiv.org/abs/1707.04348,
   Natural Boundary Conditions for Smoothing in Geometry Processing
   (Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)
   The interior vertices are NOT set to zero yet.

  @tparam DerivedV  derived type of eigen matrix for V (e.g. derived from
    MatrixXd)
  @tparam DerivedF  derived type of eigen matrix for F (e.g. derived from
    MatrixXi)
  @tparam Scalar  scalar type for eigen sparse matrix (e.g. double)
  @param[in] V  #V by dim list of mesh vertex positions
  @param[in] F  #F by 3 list of mesh elements (must be triangles)
  @param[out] H dim²⋅#V by #V Hessian matrix, each column i corresponding to V(i,:)");

}
