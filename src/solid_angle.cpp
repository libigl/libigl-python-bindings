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
#include <igl/solid_angle.h>

const char *ds_solid_angle = R"igl_Qu8mg5v7(
 Compute the signed solid angle subtended by the oriented 3d triangle (A,B,C) at some point P

Parameters
----------
     A  3D position of corner
     B  3D position of corner
     C  3D position of corner
     P  3D position of query point

Returns
-------
   Returns signed solid angle


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(solid_angle)
npe_doc(ds_solid_angle)

npe_arg(a, dense_float, dense_double)
npe_arg(b, npe_matches(a))
npe_arg(c, npe_matches(a))
npe_arg(p, npe_matches(a))


npe_begin_code()
  assert_size_equals(a, 3, "a");
  assert_size_equals(b, 3, "b");
  assert_size_equals(c, 3, "c");
  assert_size_equals(p, 3, "p");

  using Scalar = typename npe_Matrix_a::Scalar;
  using MatType = Eigen::Matrix<Scalar, 3, 1>;
  //fixme whit eigen flag
  Eigen::Map<MatType> a_tmp(&a(0, 0), a.size());
  Eigen::Map<MatType> b_tmp(&b(0, 0), b.size());
  Eigen::Map<MatType> c_tmp(&c(0, 0), c.size());
  Eigen::Map<MatType> p_tmp(&p(0, 0), p.size());

  double res = igl::solid_angle(a_tmp, b_tmp, c_tmp, p_tmp);
  return res;

npe_end_code()


