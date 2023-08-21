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
#include <igl/rigid_alignment.h>

const char *ds_rigid_alignment = R"igl_Qu8mg5v7(

Find the rigid transformation that best aligns the 3D points X to their
corresponding points P with associated normals N.

min       ‖(X*R+t-P)'N‖²
R∈SO(3)
t∈R³

Parameters
----------

X  #X by 3 list of query points
P  #X by 3 list of corresponding (e.g., closest) points
N  #X by 3 list of unit normals for each row in P

Returns
-------

R  3 by 3 rotation matrix
t  1 by 3 translation vector

See also
--------
icp

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(rigid_alignment)
npe_doc(ds_rigid_alignment)

npe_arg(x, dense_float, dense_double)
npe_arg(p, npe_matches(x))
npe_arg(n, npe_matches(x))


npe_begin_code()
  assert_cols_equals(x, 3, "x");

  assert_rows_match(x, p, "x", "p");
  assert_rows_match(x, n, "x", "n");

  assert_cols_match(x, p, "x", "p");
  assert_cols_match(x, n, "x", "n");

  EigenDense<npe_Scalar_x> x_copy = x;

  EigenDense<npe_Scalar_x> r;
  Eigen::Matrix<npe_Scalar_x, 1, 3> t;
  igl::rigid_alignment(x_copy, p, n, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


