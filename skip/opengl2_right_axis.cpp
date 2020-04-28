#include <npe.h>
#include <typedefs.h>






#include <igl/right_axis.h>

const char* ds_right_axis = R"igl_Qu8mg5v7(

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

 Determines the right axis or depth axis of the current gl matrix
     Outputs:
       x  pointer to x-coordinate in scene coordinates of the un-normalized
         right axis 
       y  pointer to y-coordinate in scene coordinates of the un-normalized
         right axis 
       z  pointer to z-coordinate in scene coordinates of the un-normalized
         right axis
       mv pointer to modelview matrix
    
     Note: Right axis is returned *UN-normalized*
)igl_Qu8mg5v7";

npe_function(right_axis)
npe_doc(ds_right_axis)



npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::right_axis(x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()
#include <igl/right_axis.h>

const char* ds_right_axis = R"igl_Qu8mg5v7(
See right_axis for the documentation.
)igl_Qu8mg5v7";

npe_function(right_axis)
npe_doc(ds_right_axis)

npe_arg(mv, double *)


npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::right_axis(mv, x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()


