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






#include <igl/two_axis_valuator_fixed_up.h>

const char *ds_two_axis_valuator_fixed_up = R"igl_Qu8mg5v7(

Applies a two-axis valuator drag rotation (as seen in Maya/Studio max) to a given rotation.

Parameters
----------
w  width of the trackball context
h  height of the trackball context
speed  controls how fast the trackball feels, 1 is normal
down_quat  rotation at mouse down, i.e. the rotation we're applying the
  trackball motion to (as quaternion). **Note:** Up-vector that is fixed
  is with respect to this rotation.
down_x position of mouse down
down_y position of mouse down
mouse_x  current x position of mouse
mouse_y  current y position of mouse

Returns
-------
quat  the resulting rotation (as quaternion)

See also
--------
snap_to_fixed_up

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(two_axis_valuator_fixed_up)
npe_doc(ds_two_axis_valuator_fixed_up)

npe_arg(w, int)
npe_arg(h, int)
npe_arg(speed, double)
npe_arg(down_quat, dense_float, dense_double)
npe_arg(down_x, int)
npe_arg(down_y, int)
npe_arg(mouse_x, int)
npe_arg(mouse_y, int)


npe_begin_code()
  assert_size_equals(down_quat, 4, "down_quat");
  Eigen::Quaternion<double> down_quat_copy;
  if (down_quat.cols() == 1)
  {
    down_quat_copy.x() = down_quat(0, 0);
    down_quat_copy.y() = down_quat(1, 0);
    down_quat_copy.z() = down_quat(2, 0);
    down_quat_copy.w() = down_quat(3, 0);
  }
  else
  {
    down_quat_copy.x() = down_quat(0, 0);
    down_quat_copy.y() = down_quat(0, 1);
    down_quat_copy.z() = down_quat(0, 2);
    down_quat_copy.w() = down_quat(0, 3);
  }

  Eigen::Quaternion<double> quat_copy;
  igl::two_axis_valuator_fixed_up(w, h, speed, down_quat_copy, down_x, down_y, mouse_x, mouse_y, quat_copy);
  EigenDenseLike<npe_Matrix_down_quat> quat(4, 1);
  quat(0) = quat_copy.x();
  quat(1) = quat_copy.y();
  quat(2) = quat_copy.z();
  quat(3) = quat_copy.w();

  return npe::move(quat);

npe_end_code()


