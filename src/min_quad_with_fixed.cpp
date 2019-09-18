//TODO: __example remove __copy

#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/min_quad_with_fixed.h>

const char *ds_min_quad_with_fixed = R"igl_Qu8mg5v7(

MIN_QUAD_WITH_FIXED Minimize a quadratic energy of the form
trace( 0.5*Z'*A*Z + Z'*B + constant )
subject to
Z(known,:) = Y, and
Aeq*Z = Beq

Parameters
----------
A  n by n matrix of quadratic coefficients
B  n by 1 column of linear coefficients
known list of indices to known rows in Z
Y  list of fixed values corresponding to known rows in Z
Aeq  m by n list of linear equality constraint coefficients
Beq  m by 1 list of linear equality constraint constant values
is_A_pd  flag specifying whether A(unknown,unknown) is positive definite


Returns
-------
Z  n by k solution

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(min_quad_with_fixed)
npe_doc(ds_min_quad_with_fixed)

npe_arg(A, sparse_double)
npe_arg(B, dense_double)
npe_arg(known, dense_int, dense_long, dense_longlong)
npe_arg(Y, dense_double)
npe_arg(Aeq, sparse_double)
npe_arg(Beq, dense_double)
npe_arg(is_A_pd, bool)


npe_begin_code()

  assert_nonzero_rows(A, "A");
  if(Aeq.size() > 0)
    assert_cols_match(A, Aeq, "A", "Aeq");
  assert_rows_match(A, B, "A", "B");
  assert_cols_match(B, Y, "B", "Y");
  if (Beq.size() > 0)
    assert_cols_match(B, Beq, "B", "Beq");
  assert_rows_match(Aeq, Beq, "Aeq", "Beq");

  Eigen::SparseMatrix<double> A_copy = A;
  Eigen::SparseMatrix<double> Aeq_copy = Aeq;

  Eigen::MatrixXd sol;

  bool ok = igl::min_quad_with_fixed(A_copy, B, known, Y, Aeq_copy, Beq, is_A_pd, sol);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> sol_row_major = sol;
  return std::make_pair(ok, npe::move(sol_row_major));

npe_end_code()
