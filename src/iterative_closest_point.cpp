#include "default_types.h"
#include <igl/iterative_closest_point.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto iterative_closest_point(
    const nb::DRef<const Eigen::MatrixXN> &VX,
    const nb::DRef<const Eigen::MatrixXI> &FX,
    const nb::DRef<const Eigen::MatrixXN> &VY,
    const nb::DRef<const Eigen::MatrixXI> &FY,
    const int num_samples,
    const int max_iters)
  {
    // t must be a row vector type (MaxRowsAtCompileTime==1) for rowwise()+t inside igl
    Eigen::MatrixXd R;
    Eigen::RowVectorXd t;
    igl::iterative_closest_point(VX, FX, VY, FY, num_samples, max_iters, R, t);
    return std::make_tuple(Eigen::MatrixXN(R), Eigen::MatrixXN(t));
  }
}

void bind_iterative_closest_point(nb::module_ &m)
{
  m.def("iterative_closest_point", &pyigl::iterative_closest_point,
    "VX"_a, "FX"_a, "VY"_a, "FY"_a,
    "num_samples"_a = 100, "max_iters"_a = 100,
    R"(Find rigid transformation placing mesh X onto mesh Y via ICP.

Minimizes: ∫_X inf_y∈Y ‖x*R+t - y‖² dx

@param[in] VX  #VX by 3 mesh X vertex positions
@param[in] FX  #FX by 3 mesh X triangle indices
@param[in] VY  #VY by 3 mesh Y vertex positions
@param[in] FY  #FY by 3 mesh Y triangle indices
@param[in] num_samples  number of random samples per iteration
@param[in] max_iters  maximum iterations
@return R  3 by 3 rotation matrix
@return t  1 by 3 translation vector)");
}
