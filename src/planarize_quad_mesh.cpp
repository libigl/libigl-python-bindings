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
#include <igl/planarize_quad_mesh.h>

const char* ds_planarize_quad_mesh = R"igl_Qu8mg5v7(
Planarize a quad mesh.

Parameters
----------
v : #v by 3 array of mesh vertex 3D positions
f : #f by 4 array of face (quad) indices
max_iter : maximum numbers of iterations
threshold : minimum allowed threshold for non-planarity

Returns
-------
out : #v by 3 array of planar mesh vertex 3D positions

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(planarize_quad_mesh)
npe_doc(ds_planarize_quad_mesh)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(max_iter, int)
npe_arg(threshold, double)


npe_begin_code()
  assert_valid_3d_quad_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;

  EigenDenseLike<npe_Matrix_v> out;
  igl::planarize_quad_mesh(v_copy, f_copy, max_iter, threshold, out);
  return npe::move(out);

npe_end_code()


