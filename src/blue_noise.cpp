// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Peter Kulits
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/blue_noise.h>

const char* ds_blue_noise = R"igl_Qu8mg5v7(
"Fast Poisson Disk Sampling in Arbitrary Dimensions" [Bridson 2007]

For very dense samplings this is faster than (up to 2x) cyCodeBase's
implementation of "Sample Elimination for Generating Poisson Disk Sample
Sets" [Yuksel 2015]. YMMV
Parameters
----------
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh triangle indices into rows of V
     r  Poisson disk radius (evaluated according to Euclidean distance on V)

Returns
-------
     B  #P by 3 list of barycentric coordinates, ith row are coordinates of
       ith sampled point in face FI(i)
     FI  #P list of indices into F
     P  #P by dim list of sample positions.

See also
--------
random_points_on_mesh

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(blue_noise)
npe_doc(ds_blue_noise)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(r, double)


npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> b;
  Eigen::VectorXi fi;
  EigenDenseLike<npe_Matrix_v> p;
  igl::blue_noise(v, f, r, b, fi, p);
  return std::make_tuple(npe::move(b), npe::move(fi), npe::move(p));

npe_end_code()
