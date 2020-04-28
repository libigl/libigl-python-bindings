#include <npe.h>
#include <typedefs.h>






#include <igl/up_axis.h>

const char* ds_up_axis = R"igl_Qu8mg5v7(

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

 Determines the up axis or depth axis of the current gl matrix
     Outputs:
       x  pointer to x-coordinate in scene coordinates of the un-normalized
         up axis 
       y  pointer to y-coordinate in scene coordinates of the un-normalized
         up axis 
       z  pointer to z-coordinate in scene coordinates of the un-normalized
         up axis
         mv pointer to modelview matrix
    
     Note: Up axis is returned *UN-normalized*
)igl_Qu8mg5v7";

npe_function(up_axis)
npe_doc(ds_up_axis)



npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::up_axis(x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()
#include <igl/up_axis.h>

const char* ds_up_axis = R"igl_Qu8mg5v7(
See up_axis for the documentation.
)igl_Qu8mg5v7";

npe_function(up_axis)
npe_doc(ds_up_axis)

npe_arg(mv, double *)


npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::up_axis(mv, x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()


