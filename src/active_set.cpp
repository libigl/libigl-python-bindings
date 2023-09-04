// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/active_set.h>

const char *ds_active_set = R"igl_Qu8mg5v7(
ACTIVE_SET Minimize quadratic energy

0.5*Z'*A*Z + Z'*B + C with constraints
that Z(known) = Y, optionally also subject to the constraints Aeq*Z = Beq,
and further optionally subject to the linear inequality constraints that
Aieq*Z <= Bieq and constant inequality constraints lx <= x <= ux

Parameters
----------
A  n by n matrix of quadratic coefficients
B  n by 1 column of linear coefficients
known  list of indices to known rows in Z
Y  list of fixed values corresponding to known rows in Z
Aeq  meq by n list of linear equality constraint coefficients
Beq  meq by 1 list of linear equality constraint constant values
Aieq  mieq by n list of linear inequality constraint coefficients
Bieq  mieq by 1 list of linear inequality constraint constant values
lx  n by 1 list of lower bounds [] implies -Inf
ux  n by 1 list of upper bounds [] implies Inf
params  struct of additional parameters (see below)
Z  if not empty, is taken to be an n by 1 list of initial guess values (see output)
Returns
-------
Z n by 1 list of solution values
Returns SOLVER_STATUS_CONVERGED = 0, SOLVER_STATUS_MAX_ITER = 1, SOLVER_STATUS_ERROR = 2,

See also
--------

Notes
-----
For a harmonic solve on a mesh with 325K facets, matlab 2.2 secs, igl / min_quad_with_fixed.h 7.1 secs

Known Bugs : rows of[Aeq; Aieq] **must **be linearly independent.Should be using QR decomposition otherwise : http : //www.okstate.edu/sas/v8/sashtml/ormp/chap5/sect32.htm


Examples
--------

)igl_Qu8mg5v7";

//NONe and dense_like
npe_function(active_set)
npe_doc(ds_active_set)
npe_arg(A, sparse_float, sparse_double)
npe_arg(B, dense_float, dense_double)
npe_arg(known, dense_int32, dense_int64)
npe_arg(Y, npe_matches(B))
npe_arg(Aeq, npe_matches(A))
npe_arg(Beq, npe_matches(B))
npe_arg(Aieq, npe_matches(A))
npe_arg(Bieq, npe_matches(B))
npe_arg(lx, npe_matches(B))
npe_arg(ux, npe_matches(B))

npe_default_arg(Auu_pd, bool, false)
npe_default_arg(max_iter, int, 100)
npe_default_arg(inactive_threshold, double, igl::DOUBLE_EPS)
npe_default_arg(constraint_threshold, double, igl::DOUBLE_EPS)
npe_default_arg(solution_diff_threshold, double, igl::DOUBLE_EPS)

npe_begin_code()
  assert_cols_equals(A, A.rows(), "A");
  assert_rows_match(A, B, "A", "B");
  assert_cols_equals(B, 1, "B");

  assert_cols_match(A, Aeq, "A", "Aeq");
  assert_rows_match(Aeq, Beq, "Aeq", "Beq");
  assert_cols_equals(Beq, 1, "Beq");

  assert_rows_match(Aieq, Bieq, "Aieq", "Bieq");

  if(Aieq.size() > 0)
  {
    assert_cols_match(A, Aieq, "A", "Aieq");
    assert_cols_equals(Bieq, 1, "Bieq");
  }

  if(lx.size() > 0)
  {
    assert_rows_match(A, lx, "A", "lx");
    assert_cols_equals(lx, 1, "lx");
  }

  if (ux.size() > 0)
  {
    assert_rows_match(A, ux, "A", "ux");
    assert_cols_equals(ux, 1, "ux");
  }

  Eigen::SparseMatrix<double> A_copy = A.template cast<double>();
  Eigen::VectorXd B_copy = B.template cast<double>();
  Eigen::VectorXi known_copy = known.template cast<int>();
  Eigen::VectorXd Y_copy = Y.template cast<double>();
  Eigen::SparseMatrix<double> Aeq_copy = Aeq.template cast<double>();
  Eigen::VectorXd Beq_copy = Beq.template cast<double>();
  Eigen::SparseMatrix<double> Aieq_copy;
  Eigen::VectorXd Bieq_copy;

  if(Aieq.size() > 0)
  {
    Aieq_copy = Aieq.template cast<double>();
    Bieq_copy = Bieq.template cast<double>();
  }

  Eigen::VectorXd lx_copy;
  if(lx.size() > 0)
    lx_copy = lx.template cast<double>();
  Eigen::VectorXd ux_copy;
  if (ux.size() > 0)
    ux_copy = ux.template cast<double>();

  igl::active_set_params params;
  params.Auu_pd = Auu_pd;
  params.max_iter = max_iter;
  params.inactive_threshold = inactive_threshold;
  params.constraint_threshold = constraint_threshold;
  params.solution_diff_threshold = solution_diff_threshold;

  Eigen::VectorXd Z;

  auto res = igl::active_set(A_copy, B_copy, known_copy, Y_copy, Aeq_copy, Beq_copy, Aieq_copy, Bieq_copy, lx_copy, ux_copy, params, Z);
  EigenDenseLike<npe_Matrix_B> Z_row_major = Z.template cast<typename npe_Matrix_B::Scalar>();

  return std::make_tuple(int(res), npe::move(Z_row_major));

  npe_end_code()
