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
#include <igl/barycenter.h>

const char* ds_barycenter = R"igl_Qu8mg5v7(
Compute the barycenter of every simplex

Parameters
----------
v : #v x dim matrix of vertex coordinates
f : #f x simplex_size  matrix of indices of simplex corners into V

Returns
-------
A #f x dim matrix where each row is the barycenter of each simplex

See also
--------

Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(barycenter)
npe_doc(ds_barycenter)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()
  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenDenseLike<npe_Matrix_v> bc;
  igl::barycenter(v, f, bc);
  return npe::move(bc);

npe_end_code()


