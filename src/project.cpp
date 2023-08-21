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
#include <igl/project.h>

const char *ds_project = R"igl_Qu8mg5v7(
Project

Parameters
----------
V  #V by 3 list of object points
model  model matrix
proj  projection matrix
viewport  viewport vector

Returns
-------
P  #V by 3 list of screen space points

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(v, dense_float, dense_double)
npe_arg(model, npe_matches(v))
npe_arg(proj, npe_matches(v))
npe_arg(viewport, npe_matches(v))


npe_begin_code()
  assert_nonzero_rows(v, "v");
  assert_cols_equals(v, 3, "v");
  assert_rows_equals(model, 4, "model");
  assert_cols_equals(model, 4, "model");

  assert_rows_equals(proj, 4, "proj");
  assert_cols_equals(proj, 4, "proj");

  assert_size_equals(viewport, 4, "viewport");

  Eigen::Matrix<npe_Scalar_v, 4, 1> viewport_copy;
  for(int i = 0; i < 4; ++i){
    if(viewport.cols() == 1)
      viewport_copy(i) = viewport(i, 0);
    else
      viewport_copy(i) = viewport(0, i);
  }

  EigenDense<npe_Scalar_v> p;
  igl::project(v, model, proj, viewport_copy, p);
  return npe::move(p);

npe_end_code()
