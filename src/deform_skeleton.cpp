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






#include <igl/deform_skeleton.h>

const char *ds_deform_skeleton = R"igl_Qu8mg5v7(
Deform a skeleton.
Parameters
----------
C  #C by 3 list of joint positions
BE #BE by 2 list of bone edge indices
T  #BE*4 by 3 list of stacked transformation matrix

Returns
-------
CT  #BE*2 by 3 list of deformed joint positions
BET  #BE by 2 list of bone edge indices (maintains order)
See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(deform_skeleton)
npe_doc(ds_deform_skeleton)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_int32, dense_int64)
npe_arg(t, dense_float, dense_double)

npe_begin_code()
  assert_nonzero_rows(c, "C");
  assert_cols_equals(c, 3, "C");
  assert_rows_equals(t, be.rows()*4, "T");
  assert_cols_equals(be, 2, "BE");
  assert_cols_equals(t, 3, "T");

  Eigen::MatrixXd c_copy = c.template cast<double>();
  Eigen::MatrixXi be_copy = be.template cast<int>();
  Eigen::MatrixXd t_copy = t.template cast<double>();

  Eigen::MatrixXd ct;
  Eigen::MatrixXi bet;
  igl::deform_skeleton(c_copy, be_copy, t_copy, ct, bet);

  EigenDenseLike<npe_Matrix_c> ct_row_major = ct.template cast<typename npe_Matrix_c::Scalar>();
  EigenDenseLike<npe_Matrix_be> bet_row_major = bet.template cast<typename npe_Matrix_be::Scalar>();
  return std::make_tuple(npe::move(ct_row_major), npe::move(bet_row_major));

npe_end_code()
