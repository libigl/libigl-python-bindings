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
#include <igl/is_border_vertex.h>
#include <pybind11/stl.h>

const char *ds_is_border_vertex = R"igl_Qu8mg5v7(
Determine vertices on open boundary of a (manifold) mesh with triangle faces F
Parameters
----------
  V  #V by dim list of vertex positions
  F  #F by 3 list of triangle indices

Returns
-------
#V vector of bools revealing whether vertices are on boundary

See also
--------


Notes
-----
Known Bugs:
   - assumes mesh is edge manifold

Examples
--------



)igl_Qu8mg5v7";

npe_function(is_border_vertex)
npe_doc(ds_is_border_vertex)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);
  const auto res = igl::is_border_vertex(f);
  return res;

npe_end_code()


