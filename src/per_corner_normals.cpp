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
#include <igl/per_corner_normals.h>

const char *ds_per_corner_normals = R"igl_Qu8mg5v7(

Compute vertex normals via vertex position list, face list

Parameters
----------
V  #V by 3 eigen Matrix of mesh vertex 3D positions
F  #F by 3 eigen Matrix of face (triangle) indices
corner_threshold  threshold in degrees on sharp angles

Returns
-------
CN  #F*3 by 3 eigen Matrix of mesh vertex 3D normals, where the normal for corner F(i,j) is at CN(i*3+j,:)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(per_corner_normals)
npe_doc(ds_per_corner_normals)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(corner_threshold, double)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> n;
  igl::per_corner_normals(v, f, corner_threshold, n);
  return npe::move(n);

npe_end_code()

