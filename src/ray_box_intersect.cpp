// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>



#include <igl/ray_box_intersect.h>

const char *ds_ray_box_intersect = R"igl_Qu8mg5v7(
 Determine whether a ray origin+t*dir and box intersect within the ray's parameterized
   range (t0,t1)

Parameters
----------
source  3-vector origin of ray
dir  3-vector direction of ray
box_min  min axis aligned box
box_max  max axis aligned box
t0  hit only if hit.t less than t0
t1  hit only if hit.t greater than t1

Returns
-------
true if hit
tmin  minimum of interval of overlap within [t0,t1]
tmax  maximum of interval of overlap within [t0,t1]

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(ray_box_intersect)
npe_doc(ds_ray_box_intersect)

npe_arg(source, dense_float, dense_double)
npe_arg(dir, npe_matches(source))
npe_arg(box_min, npe_matches(source))
npe_arg(box_max, npe_matches(source))
npe_arg(t0, double)
npe_arg(t1, double)


npe_begin_code()
  assert_size_equals(source, 3, "source");
  assert_size_equals(dir, 3, "dir");
  assert_size_equals(box_min, 3, "box_min");
  assert_size_equals(box_max, 3, "box_max");

  Eigen::Matrix<double, 3, 1> dir_copy = dir.template cast<double>();
  Eigen::Matrix<double, 3, 1> source_copy = source.template cast<double>();

  Eigen::AlignedBox<double, 3> box_copy(box_min.template cast<double>(), box_max.template cast<double>());

  double tmin;
  double tmax;

  double t0_copy = t0;
  double t1_copy = t1;
  bool hit = igl::ray_box_intersect(source_copy, dir_copy, box_copy, t0_copy, t1_copy, tmin, tmax);
  return std::make_tuple(hit, tmin, tmax);

npe_end_code()


