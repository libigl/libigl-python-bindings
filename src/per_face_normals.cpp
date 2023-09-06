// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __miss

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/per_face_normals.h>

const char* ds_per_face_normals = R"igl_Qu8mg5v7(

Compute face normals via vertex position list, face list

Parameters
----------
V  #V by 3 eigen Matrix of mesh vertex 3D positions
F  #F by 3 eigen Matrix of face (triangle) indices
Z  3 vector normal given to faces with degenerate normal.

Returns
-------
N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals

See also
--------


Notes
-----
None

Examples
--------
Give degenerate faces (1/3,1/3,1/3)^0.5
per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);

)igl_Qu8mg5v7";

npe_function(per_face_normals)
npe_doc(ds_per_face_normals)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(z, npe_matches(v))


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> n;
  igl::per_face_normals(v, f, z, n);
  return npe::move(n);

npe_end_code()

