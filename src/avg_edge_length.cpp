// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <igl/avg_edge_length.h>

const char* ds_avg_edge_length = R"igl_Qu8mg5v7(
Compute the average edge length for the given triangle mesh.

Parameters
----------
v : array_like #v by 3 vertex array
f : f #f by simplex-size list of mesh faces (must be simplex)

Returns
-------
l : average edge length

See also
--------
adjacency_matrix

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> length = avg_edge_length(v, f)
)igl_Qu8mg5v7";

npe_function(avg_edge_length)
npe_doc(ds_avg_edge_length)
npe_arg(v, dense_double, dense_float)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  return igl::avg_edge_length(v, f);

npe_end_code()


