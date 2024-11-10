#include "default_types.h"
#include <igl/bbw.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <limits>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for bbw function
  auto bbw(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::VectorXI> &b,
    const nb::DRef<const Eigen::MatrixXN> &bc,
    const nb::DRef<const Eigen::MatrixXN> &W0,
    const bool partition_unity,
    const int verbosity,
    const int max_iter,
    const double inactive_threshold,
    const double constraint_threshold,
    const double solution_diff_threshold)
  {
    igl::BBWData bbw_data;
    bbw_data.partition_unity = partition_unity;
    bbw_data.verbosity = verbosity;
    bbw_data.active_set_params.max_iter = max_iter;
    bbw_data.active_set_params.inactive_threshold = inactive_threshold;
    bbw_data.active_set_params.constraint_threshold = constraint_threshold;
    bbw_data.active_set_params.solution_diff_threshold = solution_diff_threshold;
    bbw_data.W0 = W0;

    Eigen::MatrixXN W;
    if(!igl::bbw(V, Ele, b, bc, bbw_data, W))
    {
      throw std::runtime_error("bbw: failed to compute weights");
    }
    return W;
  }
}

// Bind the wrapper to the Python module
void bind_bbw(nb::module_ &m)
{
  igl::BBWData bbw_data;
  m.def(
    "bbw",
    &pyigl::bbw,
    "V"_a,
    "Ele"_a,
    "b"_a,
    "bc"_a,
    "W0"_a=Eigen::MatrixXN(),
    "partition_unity"_a=bbw_data.partition_unity,
    "verbosity"_a=bbw_data.verbosity,
    "max_iter"_a=bbw_data.active_set_params.max_iter,
    "inactive_threshold"_a=bbw_data.active_set_params.inactive_threshold,
    "constraint_threshold"_a=bbw_data.active_set_params.constraint_threshold,
    "solution_diff_threshold"_a=bbw_data.active_set_params.solution_diff_threshold,
R"(Compute Bounded Biharmonic Weights on a given domain (V,Ele) with a given
set of boundary conditions

@tparam DerivedV  derived type of eigen matrix for V (e.g. MatrixXd)
@tparam DerivedF  derived type of eigen matrix for F (e.g. MatrixXi)
@tparam Derivedb  derived type of eigen matrix for b (e.g. VectorXi)
@tparam Derivedbc  derived type of eigen matrix for bc (e.g. MatrixXd)
@tparam DerivedW  derived type of eigen matrix for W (e.g. MatrixXd)
@param[in] V  #V by dim vertex positions
@param[in] Ele  #Elements by simplex-size list of element indices
@param[in] b  #b boundary indices into V
@param[in] bc #b by #W list of boundary values
@param[in,out] data  object containing options, initial guess --> solution and results
@param[out] W  #V by #W list of *unnormalized* weights to normalize use
   igl::normalize_row_sums(W,W))"
    );
}



