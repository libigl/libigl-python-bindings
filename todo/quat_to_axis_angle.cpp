#include <npe.h>
#include <typedefs.h>






#include <igl/quat_to_axis_angle.h>

const char* ds_quat_to_axis_angle = R"igl_Qu8mg5v7(

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

 Convert quat representation of a rotation to axis angle
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Inputs:
     q quaternion
   Outputs:
     axis  3d vector
     angle  scalar in radians
)igl_Qu8mg5v7";

npe_function(quat_to_axis_angle)
npe_doc(ds_quat_to_axis_angle)

npe_arg(q, Q_type *)


npe_begin_code()

  Q_type * axis;
  Q_type & angle;
  igl::quat_to_axis_angle(q, axis, angle);
  return std::make_tuple(npe::move(axis), npe::move(angle));

npe_end_code()
#include <igl/quat_to_axis_angle_deg.h>

const char* ds_quat_to_axis_angle_deg = R"igl_Qu8mg5v7(

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

 Wrapper with angle in degrees
)igl_Qu8mg5v7";

npe_function(quat_to_axis_angle_deg)
npe_doc(ds_quat_to_axis_angle_deg)

npe_arg(q, Q_type *)


npe_begin_code()

  Q_type * axis;
  Q_type & angle;
  igl::quat_to_axis_angle_deg(q, axis, angle);
  return std::make_tuple(npe::move(axis), npe::move(angle));

npe_end_code()


