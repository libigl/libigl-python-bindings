// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <common.h>
#include <igl/snap_points.h>


const char *ds_snap_points = R"igl_Qu8mg5v7(
SNAP_POINTS snap list of points C to closest of another list of points V
[I,minD,VI] = snap_points(C,V)

Parameters
----------
C  #C by dim list of query point positions
V  #V by dim list of data point positions

Returns
-------
I  #C list of indices into V of closest points to C
minD  #C list of squared (^p) distances to closest points
VI  #C by dim list of new point positions, VI = V(I,:)

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(snap_points)
npe_doc(ds_snap_points)

npe_arg(c, dense_float, dense_double)
npe_arg(v, npe_matches(c))


npe_begin_code()
  assert_cols_match(c, v, "c", "v");
  assert_nonzero_rows(c, "c");
  assert_nonzero_rows(v, "v");

  EigenDenseInt i;
  EigenDense<npe_Scalar_c> min_d;
  EigenDense<npe_Scalar_c> vi;
  igl::snap_points(c, v, i, min_d, vi);
  return std::make_tuple(npe::move(i), npe::move(min_d), npe::move(vi));

npe_end_code()
