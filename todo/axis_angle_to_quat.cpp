#include <npe.h>
#include <typedefs.h>






#include <igl/axis_angle_to_quat.h>

const char* ds_axis_angle_to_quat = R"igl_Qu8mg5v7(

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

 Convert axis angle representation of a rotation to a quaternion
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Inputs:
     axis  3d vector
     angle  scalar
   Outputs:
     quaternion
)igl_Qu8mg5v7";

npe_function(axis_angle_to_quat)
npe_doc(ds_axis_angle_to_quat)

npe_arg(axis, Q_type *)
npe_arg(angle, Q_type)


npe_begin_code()

  Q_type * out;
  igl::axis_angle_to_quat(axis, angle, out);
  return npe::move(out);

npe_end_code()


