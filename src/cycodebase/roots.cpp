#include "default_types.h"
#include <igl/cycodebase/roots.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto roots(
    const nb::DRef<const Eigen::VectorXN> &coef_in,
    const Numeric xmin,
    const Numeric xmax)
  {
    // Copy to a contiguous vector of monomial coefficients (low to high).
    const Eigen::VectorXN coef = coef_in;
    Eigen::VectorXN R;
    const int nr = igl::cycodebase::roots(coef, xmin, xmax, R);
    return std::make_tuple(nr, R);
  }
}

void bind_roots(nb::module_ &m)
{
  m.def("roots", &pyigl::roots, "coef"_a, "xmin"_a, "xmax"_a,
    R"(Find the real roots of a polynomial within an interval [xmin, xmax].

@param[in] coef  #coef list of monomial coefficients (low to high order); the
  polynomial degree is len(coef)-1
@param[in] xmin  lower bound of the search interval
@param[in] xmax  upper bound of the search interval
@return Tuple (n, R) where
  n  number of roots found in [xmin, xmax]
  R  degree-length vector whose first n entries are the roots (ascending); the
     remaining entries are NaN)");
}
