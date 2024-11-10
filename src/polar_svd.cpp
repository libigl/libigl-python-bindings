#include "default_types.h"
#include <igl/polar_svd.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto polar_svd(
    const nb::DRef<const Eigen::MatrixXN > &A,
    bool include_reflections)
  {
    Eigen::MatrixXN R, T, U, V;
    Eigen::VectorXN S;
    igl::polar_svd(A, include_reflections, R, T, U, S, V);
    return std::make_tuple(std::move(R), std::move(T), std::move(U), std::move(S), std::move(V));
  }
}

// Bind the wrapper to the Python module
void bind_polar_svd(nb::module_ &m)
{
  m.def(
    "polar_svd",
    &pyigl::polar_svd,
    "A"_a,
    "include_reflections"_a = false,
    R"(Computes the polar decomposition of a NxN matrix A using SVD.

    @param[in] A  NxN matrix to be decomposed
    @param[in] includeReflections  Whether to allow R to be a reflection (default is False)
    @param[in] return_U  If true, include the left-singular vectors U in the output (default is False)
    @param[in] return_S  If true, include the singular values S in the output (default is False)
    @param[in] return_V  If true, include the right-singular vectors V in the output (default is False)
    @return Tuple containing (R,T) and selected outputs in the order specified by the flags)");
}
