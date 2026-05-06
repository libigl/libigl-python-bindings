#include "default_types.h"
#include <igl/polar_dec.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Full decomposition: R, T, U, S, V
  auto polar_dec_full(
    const nb::DRef<const Eigen::MatrixXN> &A,
    const bool includeReflections)
  {
    // SelfAdjointEigenSolver requires non-Ref type — copy to MatrixXd
    Eigen::MatrixXd a = A;
    Eigen::MatrixXN R, T, U, S, V;
    igl::polar_dec(a, includeReflections, R, T, U, S, V);
    return std::make_tuple(R, T, U, S, V);
  }
  // Simple: just R and T
  auto polar_dec_RT(
    const nb::DRef<const Eigen::MatrixXN> &A,
    const bool includeReflections)
  {
    Eigen::MatrixXd a = A;
    Eigen::MatrixXN R, T;
    igl::polar_dec(a, includeReflections, R, T);
    return std::make_tuple(R, T);
  }
}

void bind_polar_dec(nb::module_ &m)
{
  m.def("polar_dec", &pyigl::polar_dec_RT,
    "A"_a, "include_reflections"_a = false,
    R"(Compute polar decomposition A = R*T of a matrix.

@param[in] A  n by n matrix to decompose
@param[in] include_reflections  if true, R may be a reflection (det=-1)
@return R  n by n orthogonal factor
@return T  n by n symmetric positive semi-definite stretch factor)");

  m.def("polar_dec", &pyigl::polar_dec_full,
    "A"_a, "include_reflections"_a,
    R"(Compute polar decomposition A = R*T with full SVD.

@param[in] A  n by n matrix to decompose
@param[in] include_reflections  if true, R may be a reflection (det=-1)
@return R  n by n orthogonal factor
@return T  n by n symmetric stretch factor
@return U  n by n left singular vectors
@return S  n vector of singular values
@return V  n by n right singular vectors)");
}
