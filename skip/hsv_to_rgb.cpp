#include <npe.h>
#include <typedefs.h>
#include <igl/hsv_to_rgb.h>

const char* ds_hsv_to_rgb = R"igl_Qu8mg5v7(
See hsv_to_rgb for the documentation.
)igl_Qu8mg5v7";

npe_function(hsv_to_rgb)
npe_doc(ds_hsv_to_rgb)

npe_arg(h, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  igl::hsv_to_rgb(h, r);
  return npe::move(r);

npe_end_code()






#include <igl/hsv_to_rgb.h>

const char* ds_hsv_to_rgb = R"igl_Qu8mg5v7(

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
     h  hue value (degrees: [0,360])
     s  saturation value ([0,1])
     v  value value ([0,1])
   Outputs:
     r  red value ([0,1]) 
     g  green value ([0,1])
     b  blue value ([0,1])
)igl_Qu8mg5v7";

npe_function(hsv_to_rgb)
npe_doc(ds_hsv_to_rgb)

npe_arg(hsv, T *)


npe_begin_code()

  T * rgb;
  igl::hsv_to_rgb(hsv, rgb);
  return npe::move(rgb);

npe_end_code()
#include <igl/hsv_to_rgb.h>

const char* ds_hsv_to_rgb = R"igl_Qu8mg5v7(
See hsv_to_rgb for the documentation.
)igl_Qu8mg5v7";

npe_function(hsv_to_rgb)
npe_doc(ds_hsv_to_rgb)

npe_arg(h, T &)
npe_arg(s, T &)
npe_arg(v, T &)


npe_begin_code()

  T & r;
  T & g;
  T & b;
  igl::hsv_to_rgb(h, s, v, r, g, b);
  return std::make_tuple(npe::move(r), npe::move(g), npe::move(b));

npe_end_code()


