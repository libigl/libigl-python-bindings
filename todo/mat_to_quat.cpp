#include <npe.h>
#include <typedefs.h>






#include <igl/mat4_to_quat.h>

const char* ds_mat4_to_quat = R"igl_Qu8mg5v7(

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

 Convert a OpenGL (rotation) matrix to a quaternion
  
   Input:
     m  16-element opengl rotation matrix
   Output:
     q  4-element  quaternion (not normalized)
)igl_Qu8mg5v7";

npe_function(mat4_to_quat)
npe_doc(ds_mat4_to_quat)

npe_arg(m, Q_type *)


npe_begin_code()

  Q_type * q;
  igl::mat4_to_quat(m, q);
  return npe::move(q);

npe_end_code()
#include <igl/mat3_to_quat.h>

const char* ds_mat3_to_quat = R"igl_Qu8mg5v7(

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

 Input:
     m  9-element opengl rotation matrix
)igl_Qu8mg5v7";

npe_function(mat3_to_quat)
npe_doc(ds_mat3_to_quat)

npe_arg(m, Q_type *)


npe_begin_code()

  Q_type * q;
  igl::mat3_to_quat(m, q);
  return npe::move(q);

npe_end_code()


