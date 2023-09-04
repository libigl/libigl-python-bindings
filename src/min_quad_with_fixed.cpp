// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
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
//TODO missing npe_dense_like
npe_arg(A, sparse_float, sparse_double)
// npe_arg(B, npe_dense_like(A))
npe_arg(B, dense_float, dense_double)
npe_arg(known, dense_int32, dense_int64)
npe_arg(Y, npe_matches(B))
npe_arg(Aeq, npe_matches(A))
npe_arg(Beq, npe_matches(B))
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

  Eigen::SparseMatrix<double> A_copy = A.template cast<double>();
  Eigen::SparseMatrix<double> Aeq_copy = Aeq.template cast<double>();

  Eigen::MatrixXd B_copy = B.template cast<double>();
  Eigen::MatrixXd Y_copy = Y.template cast<double>();
  Eigen::MatrixXd Beq_copy = Beq.template cast<double>();

  Eigen::MatrixXd sol;

  bool ok = igl::min_quad_with_fixed(A_copy, B_copy, known, Y_copy, Aeq_copy, Beq_copy, is_A_pd, sol);
  // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> sol_row_major = sol;
  EigenDenseLike<npe_Matrix_B> sol_row_major = sol.template cast < typename npe_Matrix_B::Scalar >();
  return std::make_pair(ok, npe::move(sol_row_major));

npe_end_code()
