#include "default_types.h"
#include <igl/bezier.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Single parameter t
  auto bezier_t(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const Numeric t)
  {
    Eigen::MatrixXN P;
    igl::bezier(V, t, P);
    return P;
  }
  // Array of parameters T
  auto bezier_T(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXN> &T)
  {
    // Copy T to compact vector for single-index access
    const Eigen::VectorXN t = T.reshaped();
    Eigen::MatrixXN P;
    igl::bezier(V, t, P);
    return P;
  }
}

void bind_bezier(nb::module_ &m)
{
  m.def("bezier", &pyigl::bezier_t, "V"_a, "t"_a,
    R"(Evaluate a polynomial Bezier curve at a single parameter value.

@param[in] V  #V by dim list of Bezier control points
@param[in] t  evaluation parameter in [0,1]
@return P  1 by dim output point)");

  m.def("bezier", &pyigl::bezier_T, "V"_a, "T"_a,
    R"(Evaluate a polynomial Bezier curve at many parameter values.

@param[in] V  #V by dim list of Bezier control points
@param[in] T  #T list of evaluation parameters in [0,1]
@return P  #T by dim output points)");
}
