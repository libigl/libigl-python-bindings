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
#include <igl/unproject_on_plane.h>

const char *ds_unproject_on_plane = R"igl_Qu8mg5v7(

Given a screen space point (u,v) and the current projection matrix (e.g.
gl_proj * gl_modelview) and viewport, _unproject_ the point into the scene
so that it lies on given plane.


Parameters
----------

UV  2-long uv-coordinates of screen space point
M  4 by 4 projection matrix
VP  4-long viewport: (corner_u, corner_v, width, height)
P  4-long plane equation coefficients: P*(X 1) = 0

Returns
-------
Z  3-long world coordinate
See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unproject_on_plane)
npe_doc(ds_unproject_on_plane)

npe_arg(uv, dense_float, dense_double)
npe_arg(m, npe_matches(uv))
npe_arg(vp, npe_matches(uv))
npe_arg(p, npe_matches(uv))


npe_begin_code()
  assert_size_equals(uv, 2, "uv");
  assert_rows_equals(m, 4, "m");
  assert_cols_equals(m, 4, "m");
  assert_size_equals(vp, 4, "uv");
  assert_size_equals(p, 4, "p");

  EigenDense<npe_Scalar_uv> uv_copy = uv;
  EigenDense<npe_Scalar_uv> m_copy = m;
  EigenDense<npe_Scalar_uv> vp_copy = vp;
  Eigen::Matrix<npe_Scalar_uv, 4, 1> p_copy = p;

  EigenDense<npe_Scalar_uv> z;
  igl::unproject_on_plane(uv_copy, m_copy, vp_copy, p_copy, z);
  return npe::move(z);

npe_end_code()


