#include <npe.h>
#include <typedefs.h>






#include <igl/rotate_by_quat.h>

const char* ds_rotate_by_quat = R"igl_Qu8mg5v7(

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

 Compute rotation of a given vector/point by a quaternion
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Inputs:
     v  input 3d point/vector
     q  input quaternion
   Outputs:
     out  result of rotation, allowed to be same as v
)igl_Qu8mg5v7";

npe_function(rotate_by_quat)
npe_doc(ds_rotate_by_quat)

npe_arg(v, Q_type *)
npe_arg(q, Q_type *)


npe_begin_code()

  Q_type * out;
  igl::rotate_by_quat(v, q, out);
  return npe::move(out);

npe_end_code()


