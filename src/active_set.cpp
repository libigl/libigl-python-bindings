#include "default_types.h"
#include <igl/active_set.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for active_set function
  auto active_set(
    const Eigen::SparseMatrixN &A,
    const nb::DRef<const Eigen::VectorXN> &B,
    const nb::DRef<const Eigen::VectorXI> &known,
    const nb::DRef<const Eigen::VectorXN> &Y,
    const Eigen::SparseMatrixN &Aeq,
    const nb::DRef<const Eigen::VectorXN> &Beq,
    const Eigen::SparseMatrixN &Aieq,
    const nb::DRef<const Eigen::VectorXN> &Bieq,
    const nb::DRef<const Eigen::VectorXN> &lx,
    const nb::DRef<const Eigen::VectorXN> &ux,
    const bool Auu_pd,
    const int max_iter,
    const double inactive_threshold,
    const double constraint_threshold,
    const double solution_diff_threshold)
  {
    igl::active_set_params params;
    params.Auu_pd = Auu_pd;
    params.max_iter = max_iter;
    params.inactive_threshold = inactive_threshold;
    params.constraint_threshold = constraint_threshold;
    params.solution_diff_threshold = solution_diff_threshold;

    Eigen::VectorXN Z;
    igl::SolverStatus status = igl::active_set(
      A, B, known, Y, Aeq, Beq, Aieq, Bieq, lx, ux, params, Z);

    if(status == igl::SOLVER_STATUS_ERROR)
    {
      throw std::runtime_error("active_set: solver failed");
    }
    return Z;
  }
}

// Bind the wrapper to the Python module
void bind_active_set(nb::module_ &m)
{
  igl::active_set_params params;
  m.def(
    "active_set",
    &pyigl::active_set,
    "A"_a,
    "B"_a,
    "known"_a      = Eigen::VectorXI(),
    "Y"_a          = Eigen::VectorXN(),
    "Aeq"_a        = Eigen::SparseMatrixN(),
    "Beq"_a        = Eigen::VectorXN(),
    "Aieq"_a       = Eigen::SparseMatrixN(),
    "Bieq"_a       = Eigen::VectorXN(),
    "lx"_a         = Eigen::VectorXN(),
    "ux"_a         = Eigen::VectorXN(),
    "Auu_pd"_a     = params.Auu_pd,
    "max_iter"_a   = params.max_iter,
    "inactive_threshold"_a      = params.inactive_threshold,
    "constraint_threshold"_a    = params.constraint_threshold,
    "solution_diff_threshold"_a = params.solution_diff_threshold,
R"(Minimize a convex quadratic energy subject to linear constraints.

Solves:
    min  0.5 * Z' * A * Z + Z' * B
     Z
    subject to
        Z(known) = Y
        Aeq * Z = Beq
        Aieq * Z <= Bieq
        lx <= Z <= ux

@param[in] A  n by n matrix of quadratic coefficients
@param[in] B  n by 1 column of linear coefficients
@param[in] known  list of indices to known rows in Z
@param[in] Y  list of fixed values corresponding to known rows in Z
@param[in] Aeq  meq by n list of linear equality constraint coefficients
@param[in] Beq  meq by 1 list of linear equality constraint constant values
@param[in] Aieq  mieq by n list of linear inequality constraint coefficients
@param[in] Bieq  mieq by 1 list of linear inequality constraint constant values
@param[in] lx  n by 1 list of lower bounds [] implies -Inf
@param[in] ux  n by 1 list of upper bounds [] implies Inf
@param[in] Auu_pd  whether Auu is positive definite {false}
@param[in] max_iter  maximum number of iterations {100}
@param[in] inactive_threshold  threshold on Lagrange multiplier values {1e-14}
@param[in] constraint_threshold  threshold on constraint violation {1e-14}
@param[in] solution_diff_threshold  threshold on solution difference {1e-14}
@return Z  n by 1 solution vector)"
  );
}
