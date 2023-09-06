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


#include <igl/triangle_fan.h>

const char *ds_triangle_fan = R"igl_Qu8mg5v7(
Given a list of faces tessellate all of the "exterior" edges forming another
   list of

Parameters
----------
E  #E by 2  list of exterior edges (see exterior_edges.h)

Returns
-------

cap  #cap by simplex_size  list of "faces" tessellating the boundary edges

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(triangle_fan)
npe_doc(ds_triangle_fan)

npe_arg(e, dense_int32, dense_int64)


npe_begin_code()
  assert_nonzero_rows(e, "e");
  assert_cols_equals(e, 2, "e");
  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::MatrixXi cap_copy;
  igl::triangle_fan(e_copy, cap_copy);
  EigenDenseLike<npe_Matrix_e> cap = cap_copy.template cast<npe_Scalar_e>();
  return npe::move(cap);

npe_end_code()
