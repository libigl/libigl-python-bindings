#include <npe.h>
#include <typedefs.h>






#include <igl/snap_to_fixed_up.h>

const char* ds_snap_to_fixed_up = R"igl_Qu8mg5v7(

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

 Snap an arbitrary rotation to a rotation resulting from a rotation about
   the y-axis then the x-axis (maintaining fixed up like
   two_axis_valuator_fixed_up.)
  
   Inputs:
     q  General rotation as quaternion
   Outputs:
     s the resulting rotation (as quaternion)
  
   See also: two_axis_valuator_fixed_up
)igl_Qu8mg5v7";

npe_function(snap_to_fixed_up)
npe_doc(ds_snap_to_fixed_up)

npe_arg(q, Eigen::Quaternion<Qtype> &)


npe_begin_code()

  Eigen::Quaternion<Qtype> & s;
  igl::snap_to_fixed_up(q, s);
  return npe::move(s);

npe_end_code()


