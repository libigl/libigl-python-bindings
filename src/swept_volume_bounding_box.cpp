// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <pybind11/functional.h>

#include <igl/swept_volume_bounding_box.h>

const char *ds_swept_volume_bounding_box = R"igl_Qu8mg5v7(
Construct an axis-aligned bounding box containing a shape undergoing a
   motion sampled at `steps` discrete momements.

Parameters
----------
n  number of mesh vertices
V  function handle so that V(i,t) returns the 3d position of vertex i at time t, for t∈[0,1]
steps  number of time steps: steps=3 --> t∈{0,0.5,1}

Returns
-------
min,max  corners of box containing mesh under motion

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(swept_volume_bounding_box)
npe_doc(ds_swept_volume_bounding_box)

npe_arg(n, int)
npe_arg(v, std::function<Eigen::RowVector3d (const int, const double)> &)
npe_arg(steps, int &)


npe_begin_code()

  Eigen::AlignedBox3d box;
  igl::swept_volume_bounding_box(n, v, steps, box);

  EigenDenseFloat mmin = box.min().template cast<typename EigenDenseFloat::Scalar>();
  EigenDenseFloat mmax = box.max().template cast<typename EigenDenseFloat::Scalar>();

  return std::make_tuple(npe::move(mmin), npe::move(mmax));

  npe_end_code()
