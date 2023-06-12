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
#include <igl/random_points_on_mesh.h>

const char* ds_random_points_on_mesh = R"igl_Qu8mg5v7(
RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.
Parameters
----------
     n  number of samples
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh triangle indices

Returns
-------
     B  n by 3 list of barycentric coordinates, ith row are coordinates of
       ith sampled point in face FI(i)
     FI  n list of indices into F

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(random_points_on_mesh)
npe_doc(ds_random_points_on_mesh)

npe_arg(n, int)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> b;
  EigenDenseLike<npe_Matrix_f> fi;
  igl::random_points_on_mesh(n, v, f, b, fi);
  return std::make_tuple(npe::move(b), npe::move(fi));

npe_end_code()
