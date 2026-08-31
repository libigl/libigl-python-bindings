#include "default_types.h"
#include <igl/ramer_douglas_peucker.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto ramer_douglas_peucker(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const Numeric tol)
  {
    Eigen::MatrixXN S;
    Eigen::VectorXI J;
    igl::ramer_douglas_peucker(P, tol, S, J);
    return std::make_tuple(S, J);
  }
}

void bind_ramer_douglas_peucker(nb::module_ &m)
{
  m.def(
    "ramer_douglas_peucker",
    &pyigl::ramer_douglas_peucker,
    "P"_a,
    "tol"_a,
R"(Ramer-Douglas-Peucker piecewise-linear curve simplification.

@param[in] P  #P by dim ordered list of vertices along the curve
@param[in] tol  tolerance (maximal Euclidean distance allowed between the new
                line and a removed vertex)
@param[out] S  #S by dim ordered list of points along the simplified curve
@param[out] J  #S list of indices into P so that S = P[J,:])");
}
