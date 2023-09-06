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
#include <igl/edges.h>

const char* ds_edges = R"igl_Qu8mg5v7(
Constructs a list of unique edges represented in a given mesh (v, f)

Parameters
----------
f : #F by dim list of mesh faces (must be triangles or tets)

Returns
-------
#e by 2 list of edges in no particular order

See also
--------
adjacency_matrix

Notes
-----

Examples
--------
>>> V, F, _ = igl.readOFF("test.off)
>>> E = igl.edges(F)

)igl_Qu8mg5v7";

npe_function(edges)
npe_doc(ds_edges)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()

  assert_valid_tet_or_tri_mesh_faces(f);
  EigenDenseLike<npe_Matrix_f> e;
  igl::edges(f, e);
  return npe::move(e);

npe_end_code()
