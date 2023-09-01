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






#include <igl/mvc.h>

const char *ds_mvc = R"igl_Qu8mg5v7(
MEAN VALUE COORDINATES

Parameters
----------
V  #V x dim list of vertex positions (dim = 2 or dim = 3)
C  #C x dim list of polygon vertex positions in counter-clockwise order (dim = 2 or dim = 3)

Returns
-------
W  weights, #V by #C matrix of weights

See also
--------


Notes
-----
Known Bugs: implementation is listed as "Broken"

Examples
--------
W = mvc(V,C)

)igl_Qu8mg5v7";

npe_function(mvc)
npe_doc(ds_mvc)

npe_arg(v, dense_float, dense_double)
npe_arg(c, npe_matches(v))


npe_begin_code()
  assert_nonzero_rows(v, "v");
  assert_nonzero_rows(c, "c");
  assert_cols_match(v, c, "v", "c");

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXd c_copy = c.template cast<double>();

  Eigen::MatrixXd w_copy;
  igl::mvc(v_copy, c_copy, w_copy);
  EigenDenseLike<npe_Matrix_v> w = w_copy.template cast<npe_Scalar_v>();
  return npe::move(w);
npe_end_code()


