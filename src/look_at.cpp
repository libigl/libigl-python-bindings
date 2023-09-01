// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/look_at.h>

const char *ds_look_at = R"igl_Qu8mg5v7(
Implementation of the deprecated gluLookAt function.


Parameters
----------
eye  3-vector of eye position
center  3-vector of center reference point
up  3-vector of up vector

Returns
-------
R  4x4 rotation matrix

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(look_at)
npe_doc(ds_look_at)

npe_arg(eye, dense_float, dense_double)
npe_arg(center, npe_matches(eye))
npe_arg(up, npe_matches(eye))


npe_begin_code()
  assert_size_equals(eye, 3, "eye");
  assert_size_equals(center, 3, "center");
  assert_size_equals(up, 3, "up");

  Eigen::Vector3d eye_copy = eye.template cast<double>();
  Eigen::Vector3d center_copy = center.template cast<double>();
  Eigen::Vector3d up_copy = up.template cast<double>();

  Eigen::MatrixXd r_copy;
  igl::look_at(eye_copy, center_copy, up_copy, r_copy);
  Eigen::Matrix<npe_Scalar_eye, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> r = r_copy.template cast<npe_Scalar_eye>();
  return npe::move(r);

npe_end_code()


