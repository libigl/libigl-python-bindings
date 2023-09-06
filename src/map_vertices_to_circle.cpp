// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/map_vertices_to_circle.h>

const char* ds_map_vertices_to_circle = R"igl_Qu8mg5v7(
Map the vertices whose indices are in a given boundary loop (bnd) on the unit circle with spacing proportional to the original boundary edge lengths.

Parameters
----------
v : #v by dim array of mesh vertex positions
b : #w list of vertex ids

Returns
-------
uv : #w by 2 list of 2D positions on the unit circle for the vertices in b

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(map_vertices_to_circle)
npe_doc(ds_map_vertices_to_circle)
npe_arg(v, dense_float, dense_double)
npe_arg(bnd, dense_int32, dense_int64)

npe_begin_code()

  assert_nonzero_rows(v, "v");
  assert_nonzero_rows(bnd, "bnd");
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::VectorXi bnd_copy = bnd.template cast<int>();
  Eigen::MatrixXd uv;
  igl::map_vertices_to_circle(v_copy, bnd_copy, uv);
  EigenDenseFloat uv_row_major = uv;
  return npe::move(uv_row_major);

npe_end_code()


