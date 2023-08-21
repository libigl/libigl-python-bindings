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


#include <igl/unproject_on_line.h>

const char *ds_unproject_on_line = R"igl_Qu8mg5v7(


Given a screen space point (u,v) and the current projection matrix (e.g.
gl_proj * gl_modelview) and viewport, _unproject_ the point into the scene
so that it lies on given line (origin and dir) and projects as closely as
possible to the given screen space point.

Parameters
----------
UV  2-long uv-coordinates of screen space point
M  4 by 4 projection matrix
VP  4-long viewport: (corner_u, corner_v, width, height)
origin  point on line
dir  vector parallel to line

Returns
-------
t  line parameter so that closest poin on line to viewer ray through UV
       lies at origin+t*dir
Z  3d position of closest point on line to viewing ray through UV

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unproject_on_line)
npe_doc(ds_unproject_on_line)

npe_arg(uv, dense_float, dense_double)
npe_arg(m, npe_matches(uv))
npe_arg(vp, npe_matches(uv))
npe_arg(origin, npe_matches(uv))
npe_arg(dir, npe_matches(uv))


npe_begin_code()
  assert_size_equals(uv, 2, "uv");
  assert_rows_equals(m, 4, "m");
  assert_cols_equals(m, 4, "m");
  assert_size_equals(vp, 4, "uv");

  assert_size_equals(origin, 3, "origin");
  assert_size_equals(dir, 3, "dir");

  EigenDense<npe_Scalar_uv> uv_copy = uv;
  EigenDense<npe_Scalar_uv> m_copy = m;
  EigenDense<npe_Scalar_uv> vp_copy = vp;
  EigenDense<npe_Scalar_uv> origin_copy = origin;
  EigenDense<npe_Scalar_uv> dir_copy = dir;

  npe_Scalar_uv t;
  igl::unproject_on_line(uv_copy, m_copy, vp_copy, origin_copy, dir_copy, t);
  npe_Matrix_uv Z = origin + dir * t;

  return std::make_tuple(double(t), npe::move(Z));

npe_end_code()

