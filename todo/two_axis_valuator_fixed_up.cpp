#include <npe.h>
#include <typedefs.h>






#include <igl/two_axis_valuator_fixed_up.h>

const char* ds_two_axis_valuator_fixed_up = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Applies a two-axis valuator drag rotation (as seen in Maya/Studio max) to a given rotation.
   Inputs:
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
   Outputs:
     quat  the resulting rotation (as quaternion)
  
   See also: snap_to_fixed_up
)igl_Qu8mg5v7";

npe_function(two_axis_valuator_fixed_up)
npe_doc(ds_two_axis_valuator_fixed_up)

npe_arg(w, int)
npe_arg(h, int)
npe_arg(speed, double)
npe_arg(down_quat, Eigen::Quaternion<Scalardown_quat> &)
npe_arg(down_x, int)
npe_arg(down_y, int)
npe_arg(mouse_x, int)
npe_arg(mouse_y, int)


npe_begin_code()

  Eigen::Quaternion<Scalarquat> & quat;
  igl::two_axis_valuator_fixed_up(w, h, speed, down_quat, down_x, down_y, mouse_x, mouse_y, quat);
  return npe::move(quat);

npe_end_code()


