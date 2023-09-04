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
#include <igl/per_vertex_normals.h>

const char* ds_per_vertex_normals = R"igl_Qu8mg5v7(
Compute vertex normals via vertex position list, face list.

Parameters
----------
v : #v by 3 array of mesh vertex 3D positions
f : #f by 3 array of face (triangle) indices
weighting : Weighting type, one of the following
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM uniform influence
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA area weighted
        -igl.PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE angle weighted

Returns
-------
n  #v by 3 array of mesh vertex 3D normals

See also
--------
per_face_normals, per_edge_normals

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> n = per_vertex_normals(v, f)
)igl_Qu8mg5v7";

npe_function(per_vertex_normals)
npe_doc(ds_per_vertex_normals)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(weighting, int, 0)

npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_UNIFORM) == 0, "PerVertexNormalWeightingType enum changed!");
  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_AREA) == 1, "PerVertexNormalWeightingType enum changed!");
  static_assert(int(igl::PER_VERTEX_NORMALS_WEIGHTING_TYPE_ANGLE) == 2, "PerVertexNormalWeightingType enum changed!");

  EigenDenseLike<npe_Matrix_v> n;
  igl::per_vertex_normals(v, f, igl::PerVertexNormalsWeightingType(weighting), n);
  return npe::move(n);

npe_end_code()


