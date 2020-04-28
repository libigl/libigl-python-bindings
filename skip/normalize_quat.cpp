#include <npe.h>
#include <typedefs.h>






#include <igl/normalize_quat.h>

const char* ds_normalize_quat = R"igl_Qu8mg5v7(

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

 Normalize a quaternion
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Inputs:
     q  input quaternion
   Outputs:
     out  result of normalization, allowed to be same as q
   Returns true on success, false if len(q) < EPS
)igl_Qu8mg5v7";

npe_function(normalize_quat)
npe_doc(ds_normalize_quat)

npe_arg(q, Q_type *)


npe_begin_code()

  Q_type * out;
  igl::normalize_quat(q, out);
  return npe::move(out);

npe_end_code()


