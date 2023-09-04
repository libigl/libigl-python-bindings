// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __missing miss the rest two functions with AABB and shoot_ray. __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/ambient_occlusion.h>

const char* ds_ambient_occlusion = R"igl_Qu8mg5v7(

Parameters
----------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of mesh face indices into V
P  #P by 3 list of origin points
N  #P by 3 list of origin normals

Returns
-------
S  #P list of ambient occusion values between 1 (fully occluded) and 0 (not occluded)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(ambient_occlusion)
npe_doc(ds_ambient_occlusion)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(p, dense_float, dense_double)
npe_arg(n, npe_matches(p))
npe_arg(num_samples, int)
npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  assert_cols_equals(p, 3, "p");
  assert_cols_equals(n, 3, "n");
  assert_nonzero_rows(p, "p");
  assert_nonzero_rows(n, "n");
  assert_shapes_match(p, n, "p", "n");

  EigenDenseLike<npe_Matrix_p> s;
  igl::ambient_occlusion(v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()
