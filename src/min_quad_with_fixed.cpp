#include "default_types.h"
#include <igl/min_quad_with_fixed.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto min_quad_with_fixed(
    const Eigen::SparseMatrixN &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::VectorXI> &known,
    const nb::DRef<const Eigen::MatrixXN> &Y,
    const Eigen::SparseMatrixN &Aeq,
    const nb::DRef<const Eigen::MatrixXN> &Beq,
    const bool pd)
  {
    Eigen::MatrixXN Z;
    bool success = igl::min_quad_with_fixed(A, B, known, Y, Aeq, Beq, pd, Z);
    
    if (!success)
    {
      throw std::runtime_error("min_quad_with_fixed: Optimization failed.");
    }
    
    return Z;
  }

  void min_quad_with_fixed_precompute(
    const Eigen::SparseMatrixN &A,
    const nb::DRef<const Eigen::VectorXI>  &known,
    const Eigen::SparseMatrixN &Aeq,
    const bool pd,
    igl::min_quad_with_fixed_data<Numeric> &data)
  {
    if(!igl::min_quad_with_fixed_precompute(A, known, Aeq, pd, data))
    {
      throw std::runtime_error("min_quad_with_fixed: Precomputation failed.");
    }
  }

  auto min_quad_with_fixed_solve(
    const igl::min_quad_with_fixed_data<Numeric> &data,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &Y,
    const nb::DRef<const Eigen::MatrixXN> &Beq)
  {
    Eigen::MatrixXN Z;
    if(!igl::min_quad_with_fixed_solve(data, B, Y, Beq, Z))
    {
      throw std::runtime_error("min_quad_with_fixed: Optimization failed.");
    }
    return Z;
  }

}

// Bind the wrapper to the Python module
void bind_min_quad_with_fixed(nb::module_ &m)
{
  nb::class_<igl::min_quad_with_fixed_data<Numeric>>(m, "min_quad_with_fixed_data")
    .def(nb::init<>())
    ;

  m.def("min_quad_with_fixed_solve", 
      &pyigl::min_quad_with_fixed_solve,
      "data"_a,
      "B"_a=Eigen::MatrixXN(),
      "Y"_a=Eigen::MatrixXN(),
      "Beq"_a=Eigen::MatrixXN(),
      R"(Solve the precomputed convex quadratic optimization problem.)")
    ;
  m.def("min_quad_with_fixed_precompute", 
      &pyigl::min_quad_with_fixed_precompute,
      "A"_a          = Eigen::SparseMatrixN(),
      "known"_a      = Eigen::VectorXI()     ,
      "Aeq"_a        = Eigen::SparseMatrixN(),
      "pd"_a         = true                  ,
      "data"_a,
      R"(Precompute convex quadratic optimization problem.)")
    ;

  m.def(
    "min_quad_with_fixed",
    &pyigl::min_quad_with_fixed,
    "A"_a          = Eigen::SparseMatrixN(),
    "B"_a          = Eigen::MatrixXN()     ,
    "known"_a      = Eigen::VectorXI()     ,
    "Y"_a          = Eigen::MatrixXN()     ,
    "Aeq"_a        = Eigen::SparseMatrixN(),
    "Beq"_a        = Eigen::MatrixXN()     ,
    "pd"_a         = true                  ,
R"(Minimize a convex quadratic energy subject to fixed values and linear equality constraints.

The function minimizes trace(0.5 * Z' * A * Z + Z' * B) subject to:
    Z(known,:) = Y, and
    Aeq * Z = Beq

@param[in] A  n by n matrix of quadratic coefficients
@param[in] B  n by k matrix of linear coefficients
@param[in] known  list of indices to known rows in Z
@param[in] Y  n by k matrix of fixed values corresponding to known rows in Z
@param[in] Aeq  m by n matrix of linear equality constraint coefficients
@param[in] Beq  m by k matrix of linear equality constraint target values
@param[in] pd  flag specifying whether A(unknown,unknown) is positive definite
@param[out] Z  solution matrix that minimizes the objective under constraints
@return Z solution matrix
)");
}
