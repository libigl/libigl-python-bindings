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
#include <igl/average_onto_vertices.h>

const char* ds_average_onto_vertices = R"igl_Qu8mg5v7(
Move a scalar field defined on faces to vertices by averaging

Parameters
----------
v : #v by vdim array of mesh vertices
f : #f by simplex_count array of simplex indices
s : #f by dim scalar field defined on simplices

Returns
-------
sv: #v by dim scalar field defined on vertices

See also
--------
average_onto_faces

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(average_onto_vertices)
npe_doc(ds_average_onto_vertices)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(s, dense_float, dense_double) // TODO: Maybe do a matches here
npe_begin_code()
  assert_valid_tet_or_tri_mesh_23d(v, f);
  assert_shape_equals(s, f.rows(), v.cols(), "s");
  EigenDenseLike<npe_Matrix_s> sv;
  igl::average_onto_vertices(v, f, s, sv);
  return npe::move(sv);

npe_end_code()


