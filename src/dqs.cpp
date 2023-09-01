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






#include <igl/dqs.h>

const char *ds_dqs = R"igl_Qu8mg5v7(
 Dual quaternion skinning

Parameters
----------
V  #V by 3 list of rest positions
W  #W by #C list of weights
vQ  #C list of rotation quaternions
vT  #C list of translation vectors

Returns
-------
U  #V by 3 list of new positions

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(dqs)
npe_doc(ds_dqs)

npe_arg(v, dense_float, dense_double)
npe_arg(w, npe_matches(v))
npe_arg(v_q, npe_matches(v))
npe_arg(v_t, npe_matches(v))

npe_begin_code()
  assert_cols_equals(v, 3, "V");
  assert_rows_equals(v_q, w.cols(), "vQ");
  assert_cols_equals(v_q, 4, "vQ");
  assert_cols_equals(v_t, 3, "vT");
  assert_rows_match(v_q, v_t, "vQ", "vT");

  typedef Eigen::Quaternion<typename npe_Matrix_v::Scalar> Quat;

  std::vector<Quat, Eigen::aligned_allocator<Quat>> v_q_copy(v_q.rows());
  for(size_t i = 0; i < v_q_copy.size(); ++i){
    v_q_copy[i].x() = v_q(i, 0);
    v_q_copy[i].y() = v_q(i, 1);
    v_q_copy[i].z() = v_q(i, 2);
    v_q_copy[i].w() = v_q(i, 3);
  }

  std::vector<Eigen::Matrix<typename npe_Matrix_v::Scalar, 3, 1>> v_t_copy(v_t.rows());
  for(size_t i = 0; i < v_t_copy.size(); ++i)
    v_t_copy[i] = v_t.row(i);

  EigenDenseLike<npe_Matrix_v> u;
  igl::dqs(v, w, v_q_copy, v_t_copy, u);
  return npe::move(u);

npe_end_code()


