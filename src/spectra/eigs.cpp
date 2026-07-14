#include "default_types.h"
#include <igl/spectra/eigs.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto eigs_type(
    const Eigen::SparseMatrixN &A,
    const Eigen::SparseMatrixN &B,
    const int k,
    const igl::EigsType type)
  {
    Eigen::MatrixXN U;
    Eigen::VectorXN S;
    if(!igl::spectra::eigs(A, B, k, type, U, S))
    {
      throw std::runtime_error("igl::spectra::eigs failed");
    }
    return std::make_tuple(U, S);
  }

  auto eigs_sigma(
    const Eigen::SparseMatrixN &A,
    const Eigen::SparseMatrixN &B,
    const int k,
    const Numeric sigma)
  {
    Eigen::MatrixXN U;
    Eigen::VectorXN S;
    if(!igl::spectra::eigs(A, B, k, sigma, U, S))
    {
      throw std::runtime_error("igl::spectra::eigs failed");
    }
    return std::make_tuple(U, S);
  }
}

void bind_eigs(nb::module_ &m)
{
  m.def(
    "eigs",
    &pyigl::eigs_type,
    "A"_a, "B"_a, "k"_a, "type"_a,
R"(Compute the first/last k eigen pairs of the generalized eigenvalue problem:

    A u = s B u

Solutions are approximate and sorted. Only EIGS_TYPE_SM (smallest magnitude)
is well supported.

@param[in] A  #A by #A symmetric sparse matrix
@param[in] B  #A by #A symmetric positive-definite sparse matrix
@param[in] k  number of eigen pairs to compute
@param[in] type  EigsType.EIGS_TYPE_SM or EigsType.EIGS_TYPE_LM
@param[out] U  #A by k matrix of sorted eigenvectors (descending)
@param[out] S  k vector of sorted eigenvalues (descending)
@return Tuple (U, S))");

  m.def(
    "eigs",
    &pyigl::eigs_sigma,
    "A"_a, "B"_a, "k"_a, "sigma"_a,
R"(Compute k eigen pairs of A u = s B u with a shift: A ← A + sigma * B.

@param[in] A  #A by #A symmetric sparse matrix
@param[in] B  #A by #A symmetric positive-definite sparse matrix
@param[in] k  number of eigen pairs to compute
@param[in] sigma  shift to apply to A
@param[out] U  #A by k matrix of sorted eigenvectors (descending)
@param[out] S  k vector of sorted eigenvalues (descending)
@return Tuple (U, S))");
}
