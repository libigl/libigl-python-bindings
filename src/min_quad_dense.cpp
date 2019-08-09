//TODO: __example remove __copy

#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/min_quad_dense.h>

const char* ds_min_quad_dense_precompute = R"igl_Qu8mg5v7(

MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C
   subject to linear constraints Aeq*Z = Beq

Parameters
----------
A  n by n matrix of quadratic coefficients
B  n by 1 column of linear coefficients
Aeq  m by n list of linear equality constraint coefficients
Beq  m by 1 list of linear equality constraint constant values
use_lu_decomposition  use lu rather than SVD


Returns
-------
S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(min_quad_dense_precompute)
npe_doc(ds_min_quad_dense_precompute)

npe_arg(a, dense_float, dense_double)
npe_arg(aeq, npe_matches(a))
npe_arg(use_lu_decomposition, bool)


npe_begin_code()

  assert_nonzero_rows(a, "a");
  assert_nonzero_rows(aeq, "aeq");
  assert_cols_match(a, aeq, "a", "aeq");
  Eigen::MatrixXd a_copy = a.template cast<double>();
  Eigen::MatrixXd aeq_copy = aeq.template cast<double>();
  Eigen::MatrixXd s;
  igl::min_quad_dense_precompute(a_copy, aeq_copy, use_lu_decomposition, s);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> s_row_major = s;
  return npe::move(s_row_major);

npe_end_code()


