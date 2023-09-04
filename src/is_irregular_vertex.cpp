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
#include <igl/is_irregular_vertex.h>
#include <pybind11/stl.h>

const char* ds_is_irregular_vertex = R"igl_Qu8mg5v7(
Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

Parameters
----------
f : #f by 3[4] array of triangle[quads] indices

Returns
-------
s : #v list of bools revealing whether vertices are singular

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(is_irregular_vertex)
npe_doc(ds_is_irregular_vertex)

npe_arg(f, dense_int32, dense_int64)

npe_begin_code()
  const std::vector<bool> res = igl::is_irregular_vertex(f);
  return res;

npe_end_code()


