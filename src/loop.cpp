// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/loop.h>

const char *ds_loop_mat = R"igl_Qu8mg5v7(

  LOOP Given the triangle mesh [V, F], where n_verts = V.rows(), computes
  newV and a sparse matrix S s.t. [newV, newF] is the subdivided mesh where
  newV = S*V.

Parameters
----------
n_verts  an integer (number of mesh vertices)
F  an m by 3 matrix of integers of triangle faces

Returns
-------

S  a sparse matrix (will become the subdivision matrix)
newF  a matrix containing the new faces

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(loop_subdivision_matrix)
npe_doc(ds_loop_mat)

npe_arg(n_verts, int)
npe_arg(f, dense_int32, dense_int64)

npe_begin_code()
  assert_valid_tri_mesh_faces(f);
  Eigen::SparseMatrix<double> S;
  EigenDenseLike<npe_Matrix_f> nf;
  igl::loop(n_verts, f, S, nf);
  return std::make_tuple(npe::move(S), npe::move(nf));
npe_end_code()





const char *ds_loop = R"igl_Qu8mg5v7(

  LOOP Given the triangle mesh [V, F], where n_verts = V.rows(), computes
  newV and a sparse matrix S s.t. [newV, newF] is the subdivided mesh where
  newV = S*V.

Parameters
----------
V an n by 3 matrix of vertices
F an m by 3 matrix of integers of triangle faces
number_of_subdivs an integer that specifies how many subdivision steps to do

Returns
-------

NV a matrix containing the new vertices
NF a matrix containing the new faces

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(loop)
npe_doc(ds_loop)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(number_of_subdivs, int, 1)

npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  EigenDenseLike<npe_Matrix_v> nv;
  EigenDenseLike<npe_Matrix_f> nf;

  igl::loop(v, f, nv, nf, number_of_subdivs);
  return std::make_tuple(npe::move(nv), npe::move(nf));
npe_end_code()
