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
#include <igl/local_basis.h>

const char* ds_local_basis = R"igl_Qu8mg5v7(
Compute a local orthogonal reference system for each triangle in the given mesh.

Parameters
----------
v : #v by 3 vertex array
f : #f by 3 array of mesh faces (must be triangles)

Returns
-------
b1 : #f by 3 array, each vector is tangent to the triangle
b2 : #f by 3 array, each vector is tangent to the triangle and perpendicular to B1
b3 : #f by 3 array, normal of the triangle

See also
--------
adjacency_matrix

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(local_basis)
npe_doc(ds_local_basis)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;

  EigenDenseLike<npe_Matrix_v> b1;
  EigenDenseLike<npe_Matrix_v> b2;
  EigenDenseLike<npe_Matrix_v> b3;
  igl::local_basis(v_copy, f_copy, b1, b2, b3);
  return std::make_tuple(npe::move(b1), npe::move(b2), npe::move(b3));

npe_end_code()


