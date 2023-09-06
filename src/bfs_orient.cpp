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
#include <igl/bfs_orient.h>

const char* ds_bfs_orient = R"igl_Qu8mg5v7(
Consistently orient faces in orientable patches using BFS.

Parameters
----------
f : #F by 3 list of faces

Returns
-------
A tuple, (ff, c) where:
 * ff is a #F by 3 list of faces which are consistently oriented with
 * c is a #F array of connected component ids

See also
--------

Notes
-----

Examples
--------
>>> v, f, _ = igl.readOFF("test.off)
>>> ff, c = igl.bfs_orient(f)

)igl_Qu8mg5v7";

npe_function(bfs_orient)
npe_doc(ds_bfs_orient)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  EigenDenseLike<npe_Matrix_f> ff, c;
  igl::bfs_orient(f, ff, c);
  return std::make_tuple(npe::move(ff), npe::move(c));

npe_end_code()
