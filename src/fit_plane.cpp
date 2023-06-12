// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/fit_plane.h>

const char* ds_fit_plane = R"igl_Qu8mg5v7(

This function fits a plane to a point cloud.

Parameters
----------
V #Vx3 matrix. The 3D point cloud, one row for each vertex.

Returns
-------
N 1x3 Vector. The normal of the fitted plane.
C 1x3 Vector. A point that lies in the fitted plane.

See also
--------

Notes
-----
From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html

Examples
--------


)igl_Qu8mg5v7";

npe_function(fit_plane)
npe_doc(ds_fit_plane)

npe_arg(v, dense_float, dense_double)


npe_begin_code()

  assert_nonzero_rows(v, "v");
  assert_cols_equals(v, 3, "v");
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::RowVector3d n;
  Eigen::RowVector3d c;
  igl::fit_plane(v_copy, n, c);
  Eigen::Matrix<typename EigenDenseFloat::Scalar, 1, 3, Eigen::RowMajor> n_row_major = n;
  Eigen::Matrix<typename EigenDenseFloat::Scalar, 1, 3, Eigen::RowMajor> c_row_major = c;
  return std::make_tuple(npe::move(n_row_major), npe::move(c_row_major));

npe_end_code()


