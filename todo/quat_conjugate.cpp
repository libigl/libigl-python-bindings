#include <npe.h>
#include <typedefs.h>






#include <igl/quat_conjugate.h>

const char* ds_quat_conjugate = R"igl_Qu8mg5v7(

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

 Compute conjugate of given quaternion
   http:en.wikipedia.org/wiki/Quaternion#Conjugation.2C_the_norm.2C_and_reciprocal
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Inputs:
     q1  input quaternion
   Outputs:
     out  result of conjugation, allowed to be same as input
)igl_Qu8mg5v7";

npe_function(quat_conjugate)
npe_doc(ds_quat_conjugate)

npe_arg(q1, Q_type *)


npe_begin_code()

  Q_type * out;
  igl::quat_conjugate(q1, out);
  return npe::move(out);

npe_end_code()


