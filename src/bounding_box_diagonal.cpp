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






#include <igl/bounding_box_diagonal.h>

const char* ds_bounding_box_diagonal = R"igl_Qu8mg5v7(

Compute the length of the diagonal of a given meshes axis-aligned bounding

Parameters
----------
V  #V by 3 list of vertex positions

Returns
-------
Returns length of bounding box diagonal

See also
--------

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(bounding_box_diagonal)
npe_doc(ds_bounding_box_diagonal)

npe_arg(v, dense_float, dense_double)


npe_begin_code()
  assert_nonzero_rows(v, "v");
  assert_cols_equals(v, 3, "v");
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  return igl::bounding_box_diagonal(v_copy);

npe_end_code()


