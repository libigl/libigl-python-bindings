// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/doublearea.h>

const char* ds_doublearea = R"igl_Qu8mg5v7(
Computes twice the area for each input triangle[quad]

Parameters
----------
v : #v by dim array of mesh vertex positions
f : #f by simplex_size array of mesh faces (must be triangles or quads)

Returns
-------
d_area : #f list of triangle[quad] double areas (SIGNED only for 2D input)

See also
--------
None

Notes
-----
Known bug: For dim==3 complexity is O(#V + #F)!! Not just O(#F). This is a big deal if you have 1million unreferenced vertices and 1 face

Examples
--------
# Mesh in (v, f)
>>> dbl_area = doublearea(v, f)
)igl_Qu8mg5v7";

npe_function(doublearea)
npe_doc(ds_doublearea)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)

npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenDenseLike<npe_Matrix_v> d_area;
  igl::doublearea(v, f, d_area);
  return npe::move(d_area);

npe_end_code()

