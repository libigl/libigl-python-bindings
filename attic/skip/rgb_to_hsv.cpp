#include <npe.h>
#include <typedefs.h>
#include <igl/rgb_to_hsv.h>

const char* ds_rgb_to_hsv = R"igl_Qu8mg5v7(
See rgb_to_hsv for the documentation.
)igl_Qu8mg5v7";

npe_function(rgb_to_hsv)
npe_doc(ds_rgb_to_hsv)

npe_arg(r, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> h;
  igl::rgb_to_hsv(r, h);
  return npe::move(h);

npe_end_code()






#include <igl/rgb_to_hsv.h>

const char* ds_rgb_to_hsv = R"igl_Qu8mg5v7(

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

 Convert RGB to HSV
  
   Inputs:
     r  red value ([0,1]) 
     g  green value ([0,1])
     b  blue value ([0,1])
   Outputs:
     h  hue value (degrees: [0,360])
     s  saturation value ([0,1])
     v  value value ([0,1])
)igl_Qu8mg5v7";

npe_function(rgb_to_hsv)
npe_doc(ds_rgb_to_hsv)

npe_arg(rgb, R *)


npe_begin_code()

  H * hsv;
  igl::rgb_to_hsv(rgb, hsv);
  return npe::move(hsv);

npe_end_code()


