#include <npe.h>
#include <typedefs.h>






#include <igl/quat_to_mat.h>

const char* ds_quat_to_mat = R"igl_Qu8mg5v7(

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

 Convert a quaternion to a 4x4 matrix
   A Quaternion, q, is defined here as an arrays of four scalars (x,y,z,w),
   such that q = x*i + y*j + z*k + w
   Input:
     quat  pointer to four elements of quaternion (x,y,z,w)  
   Output:
     mat  pointer to 16 elements of matrix
)igl_Qu8mg5v7";

npe_function(quat_to_mat)
npe_doc(ds_quat_to_mat)

npe_arg(quat, Q_type *)


npe_begin_code()

  Q_type * mat;
  igl::quat_to_mat(quat, mat);
  return npe::move(mat);

npe_end_code()


