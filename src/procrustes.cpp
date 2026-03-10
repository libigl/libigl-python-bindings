#include "default_types.h"
#include <igl/procrustes.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto procrustes(
    const nb::DRef<const Eigen::MatrixXN> &X,
    const nb::DRef<const Eigen::MatrixXN> &Y,
    const bool include_scaling,
    const bool include_reflections)
  {
    Numeric scale;
    Eigen::MatrixXN R;
    Eigen::VectorXN t;
    igl::procrustes(X, Y, include_scaling, include_reflections, scale, R, t);
    return std::make_tuple(scale, R, t);
  }
}

void bind_procrustes(nb::module_ &m)
{
  m.def("procrustes", &pyigl::procrustes,
    "X"_a, "Y"_a,
    "include_scaling"_a = false,
    "include_reflections"_a = false,
    R"(Solve the Procrustes problem: find s, R, t minimizing |s*X*R + t - Y|².

@param[in] X  #V by dim first list of points
@param[in] Y  #V by dim second list of points
@param[in] include_scaling  if true, solve for scale s
@param[in] include_reflections  if true, R may be a reflection
@return scale  scalar scale factor s
@return R  dim by dim rotation (or reflection) matrix
@return t  dim translation vector)");
}
