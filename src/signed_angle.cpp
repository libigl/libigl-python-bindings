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
#include <igl/signed_angle.h>

const char *ds_signed_angle = R"igl_Qu8mg5v7(

 Compute the signed angle subtended by the oriented 3d triangle (A,B,C) at some point P


Parameters
----------
A  2D position of corner
B  2D position of corner
P  2D position of query point

Returns
-------
returns signed angle

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(signed_angle)
npe_doc(ds_signed_angle)

npe_arg(a, dense_float, dense_double)
npe_arg(b, npe_matches(a))
npe_arg(p, npe_matches(a))


npe_begin_code()
  assert_size_equals(a, 2, "a");
  assert_size_equals(b, 2, "b");
  assert_size_equals(p, 2, "p");

  Eigen::Vector2d a_copy, b_copy, p_copy;

  if(a.cols() == 1)
  {
    a_copy(0) = a(0, 0);
    a_copy(1) = a(1, 0);
  }
  else
  {
    a_copy(0) = a(0, 0);
    a_copy(1) = a(0, 1);
  }

  if (b.cols() == 1)
  {
    b_copy(0) = b(0, 0);
    b_copy(1) = b(1, 0);
  }
  else
  {
    b_copy(0) = b(0, 0);
    b_copy(1) = b(0, 1);
  }

  if (p.cols() == 1)
  {
    p_copy(0) = p(0, 0);
    p_copy(1) = p(1, 0);
  }
  else
  {
    p_copy(0) = p(0, 0);
    p_copy(1) = p(0, 1);
  }

  const auto angle = igl::signed_angle(a_copy, b_copy, p_copy);
  return angle;

npe_end_code()


