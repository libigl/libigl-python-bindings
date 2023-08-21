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






#include <igl/ray_sphere_intersect.h>

const char *ds_ray_sphere_intersect = R"igl_Qu8mg5v7(
Compute the intersection between a ray from O in direction D and a sphere centered at C with radius r

Parameters
----------
source  origin of ray
dir  direction of ray
center  center of sphere
r  radius of sphere

Returns
-------
Returns the number of hits
t0  parameterization of first hit (set only if exists) so that hit position = o + t0*d
t1  parameterization of second hit (set only if exists)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(ray_sphere_intersect)
npe_doc(ds_ray_sphere_intersect)

npe_arg(source, dense_float, dense_double)
npe_arg(dir, npe_matches(source))
npe_arg(center, npe_matches(source))
npe_arg(r, double)


npe_begin_code()
  assert_size_equals(source, 3, "source");
  assert_size_equals(dir, 3, "dir");
  assert_size_equals(center, 3, "center");

  Eigen::Matrix<double, 3, 1> dir_copy = dir.template cast<double>();
  Eigen::Matrix<double, 3, 1> source_copy = source.template cast<double>();
  Eigen::Matrix<double, 3, 1> center_copy = center.template cast<double>();

  double t0;
  double t1;
  int inters = igl::ray_sphere_intersect(source_copy, dir_copy, center_copy, r, t0, t1);
  return std::make_tuple(inters, t0, t1);

npe_end_code()


