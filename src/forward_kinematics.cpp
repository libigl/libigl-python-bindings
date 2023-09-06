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




#include <igl/forward_kinematics.h>

const char *ds_forward_kinematics = R"igl_Qu8mg5v7(
Given a skeleton and a set of relative bone rotations compute absolute rigid transformations for each bone.
Parameters
----------
C  #C by dim list of joint positions
BE  #BE by 2 list of bone edge indices
P  #BE list of parent indices into BE
dQ  #BE list of relative rotations
dT  #BE list of relative translations

Returns
-------
vQ  #BE list of absolute rotations
vT  #BE list of absolute translations

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(forward_kinematics)
npe_doc(ds_forward_kinematics)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_int32, dense_int64)
npe_arg(p, npe_matches(be))
npe_arg(d_q, npe_matches(c))
npe_arg(d_t, dense_float, dense_double)
//TODO missing none for d_t


npe_begin_code()
  assert_cols_equals(c, 3, "C");
  assert_cols_equals(be, 2, "BE");

  assert_rows_match(d_q, be, "dQ", "BE");
  assert_cols_equals(d_q, 4, "dQ");
  if(d_t.size() > 0){
    assert_cols_equals(d_t, 3, "dT");
    assert_rows_match(d_q, d_t, "dQ", "dT");
  }

  Eigen::MatrixXd c_copy = c.template cast<double>();
  Eigen::MatrixXi be_copy = be.template cast<int>();
  Eigen::VectorXi p_copy = p.template cast<int>();

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond>> d_q_copy(d_q.rows());
  for (size_t i = 0; i < d_q_copy.size(); ++i)
  {
    d_q_copy[i].x() = d_q(i, 0);
    d_q_copy[i].y() = d_q(i, 1);
    d_q_copy[i].z() = d_q(i, 2);
    d_q_copy[i].w() = d_q(i, 3);
  }

  std::vector<Eigen::Vector3d> d_t_copy(d_t.rows());
  for (size_t i = 0; i < d_t_copy.size(); ++i)
    d_t_copy[i] = d_t.row(i).template cast<double>();

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > v_q;
  std::vector<Eigen::Vector3d> v_t;
  if (d_t_copy.empty())
    igl::forward_kinematics(c_copy, be_copy, p_copy, d_q_copy, v_q, v_t);
  else
    igl::forward_kinematics(c_copy, be_copy, p_copy, d_q_copy, d_t_copy, v_q, v_t);

  EigenDenseLike<npe_Matrix_c> v_q_out(v_q.size(), 4);
  EigenDenseLike<npe_Matrix_c> v_t_out(v_t.size(), 3);

  for (size_t i = 0; i < v_q.size(); ++i)
  {
    v_q_out(i, 0) = v_q[i].x();
    v_q_out(i, 1) = v_q[i].y();
    v_q_out(i, 2) = v_q[i].z();
    v_q_out(i, 3) = v_q[i].w();
  }

  for (size_t i = 0; i < v_t.size(); ++i)
    v_t_out.row(i) = v_t[i].template cast<typename npe_Matrix_c::Scalar>();

  return std::make_tuple(npe::move(v_q_out), npe::move(v_t_out));

  npe_end_code()