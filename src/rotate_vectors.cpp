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






#include <igl/rotate_vectors.h>

const char *ds_rotate_vectors = R"igl_Qu8mg5v7(
 Rotate the vectors V by A radiants on the tangent plane spanned by B1 and B2

Parameters
----------
V     #V by 3 eigen Matrix of vectors
A     #V eigen vector of rotation angles or a single angle to be applied to all vectors
B1    #V by 3 eigen Matrix of base vector 1
B2    #V by 3 eigen Matrix of base vector 2
Returns
-------
Returns the rotated vectors

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(rotate_vectors)
npe_doc(ds_rotate_vectors)

npe_arg(v, dense_float, dense_double)
npe_arg(a, npe_matches(v))
npe_arg(b1, npe_matches(v))
npe_arg(b2, npe_matches(v))


npe_begin_code()
  if(a.size() > 1)
    assert_rows_match(v, a, "V", "A");
  assert_rows_match(v, b1, "V", "B1");
  assert_rows_match(v, b2, "V", "B2");

  assert_cols_equals(v, 3, "V");
  assert_cols_equals(b1, 3, "B1");
  assert_cols_equals(b2, 3, "B2");
  assert_cols_equals(a, 1, "A");

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::VectorXd a_copy = a.template cast<double>();
  Eigen::MatrixXd b1_copy = b1.template cast<double>();
  Eigen::MatrixXd b2_copy = b2.template cast<double>();

  Eigen::MatrixXd res = igl::rotate_vectors(v_copy, a_copy, b1_copy, b2_copy);
  EigenDenseLike<npe_Matrix_v> res_row_maj = res.template cast<typename npe_Matrix_v::Scalar>();
  return npe::move(res_row_maj);

  npe_end_code()
