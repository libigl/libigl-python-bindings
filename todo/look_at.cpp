#include <npe.h>
#include <typedefs.h>
#include <igl/look_at.h>

const char* ds_look_at = R"igl_Qu8mg5v7(

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

 Implementation of the deprecated gluLookAt function.
  
   Inputs:
     eye  3-vector of eye position
     center  3-vector of center reference point
     up  3-vector of up vector
   Outputs:
     R  4x4 rotation matrix
  
)igl_Qu8mg5v7";

npe_function(look_at)
npe_doc(ds_look_at)

npe_arg(eye, dense_f32, dense_f64)
npe_arg(center, dense_f32, dense_f64)
npe_arg(up, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  igl::look_at(eye, center, up, r);
  return npe::move(r);

npe_end_code()


