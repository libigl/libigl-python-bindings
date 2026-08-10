#include "default_types.h"
#include <igl/cubic_monomial_bases.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cubic_monomial_bases(
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    Eigen::MatrixXN M, D;
    // B is a 6-vector of inner products (cubic_monomial_bases calls vector
    // methods on it), so it must be a vector type, not a general matrix.
    Eigen::VectorXN B;
    igl::cubic_monomial_bases(C, M, D, B);
    return std::make_tuple(M, D, B);
  }
}

void bind_cubic_monomial_bases(nb::module_ &m)
{
  m.def("cubic_monomial_bases", &pyigl::cubic_monomial_bases, "C"_a,
    R"(Compute monomial basis representations for a cubic Bézier curve.

@param[in] C  4 by dim matrix of control points for a cubic Bézier curve
@return Tuple (M, D, B) where
  M  4 by dim matrix of monomial coefficients for C(t)
  D  3 by dim matrix of monomial coefficients for dC/dt
  B  6-vector of inner products of those basis functions for C(t))");
}
