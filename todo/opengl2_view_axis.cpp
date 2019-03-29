#include <npe.h>
#include <typedefs.h>
#include <igl/view_axis.h>

const char* ds_view_axis = R"igl_Qu8mg5v7(
See view_axis for the documentation.
)igl_Qu8mg5v7";

npe_function(view_axis)
npe_doc(ds_view_axis)



npe_begin_code()

  EigenDense<npe_Scalar_> v;
  igl::  opengl2::view_axis(v);
  return npe::move(v);

npe_end_code()






#include <igl/view_axis.h>

const char* ds_view_axis = R"igl_Qu8mg5v7(

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

 Determines the view axis or depth axis of the current gl matrix
     Inputs:
       mv pointer to modelview matrix
     Outputs:
       x  pointer to x-coordinate in scene coordinates of the un-normalized
         viewing axis 
       y  pointer to y-coordinate in scene coordinates of the un-normalized
         viewing axis 
       z  pointer to z-coordinate in scene coordinates of the un-normalized
         viewing axis
    
     Note: View axis is returned *UN-normalized*
)igl_Qu8mg5v7";

npe_function(view_axis)
npe_doc(ds_view_axis)

npe_arg(mv, double *)


npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::view_axis(mv, x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()
#include <igl/view_axis.h>

const char* ds_view_axis = R"igl_Qu8mg5v7(

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

 Extract mv from current GL state.
)igl_Qu8mg5v7";

npe_function(view_axis)
npe_doc(ds_view_axis)



npe_begin_code()

  double * x;
  double * y;
  double * z;
  igl::  opengl2::view_axis(x, y, z);
  return std::make_tuple(npe::move(x), npe::move(y), npe::move(z));

npe_end_code()


