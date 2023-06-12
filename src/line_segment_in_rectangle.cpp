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






#include <igl/line_segment_in_rectangle.h>

const char *ds_line_segment_in_rectangle = R"igl_Qu8mg5v7(
Determine whether a line segment overlaps with a rectangle.

Parameters
----------
s  source point of line segment
d  dest point of line segment
A  first corner of rectangle
B  opposite corner of rectangle

Returns
-------
Returns true if line segment is at all inside rectangle

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(line_segment_in_rectangle)
npe_doc(ds_line_segment_in_rectangle)

npe_arg(s, dense_float, dense_double)
npe_arg(d, npe_matches(s))
npe_arg(a, npe_matches(s))
npe_arg(b, npe_matches(s))


npe_begin_code()
  assert_size_equals(s, 2, "s");
  assert_size_equals(d, 2, "d");
  assert_size_equals(a, 2, "a");
  assert_size_equals(b, 2, "b");

  Eigen::Vector2d s_copy = s.template cast<double>();
  Eigen::Vector2d d_copy = d.template cast<double>();
  Eigen::Vector2d a_copy = a.template cast<double>();
  Eigen::Vector2d b_copy = b.template cast<double>();

  return igl::line_segment_in_rectangle(s_copy, d_copy, a_copy, b_copy);

npe_end_code()
