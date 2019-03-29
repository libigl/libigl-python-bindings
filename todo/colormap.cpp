#include <npe.h>
#include <typedefs.h>
#include <igl/colormap.h>

const char* ds_colormap = R"igl_Qu8mg5v7(

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

 Inputs:
     cm selected colormap palette to interpolate from
     Z  #Z list of factors
     normalize  whether to normalize Z to be tightly between [0,1]
   Outputs:
     C  #C by 3 list of rgb colors
)igl_Qu8mg5v7";

npe_function(colormap)
npe_doc(ds_colormap)

npe_arg(cm, igl::ColorMapType)
npe_arg(z, dense_f32, dense_f64)
npe_arg(normalize, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  igl::colormap(cm, z, normalize, c);
  return npe::move(c);

npe_end_code()






#include <igl/colormap.h>

const char* ds_colormap = R"igl_Qu8mg5v7(

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

 Comput [r,g,b] values of the selected colormap for
   a given factor f between 0 and 1
  
   Inputs:
     c  colormap enum
     f  factor determining color value as if 0 was min and 1 was max
   Outputs:
     rgb  red, green, blue value
)igl_Qu8mg5v7";

npe_function(colormap)
npe_doc(ds_colormap)

npe_arg(cm, igl::ColorMapType)
npe_arg(f, T)


npe_begin_code()

  T * rgb;
  igl::colormap(cm, f, rgb);
  return npe::move(rgb);

npe_end_code()
#include <igl/colormap.h>

const char* ds_colormap = R"igl_Qu8mg5v7(

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

 Outputs:
     r  red value
     g  green value
     b  blue value
)igl_Qu8mg5v7";

npe_function(colormap)
npe_doc(ds_colormap)

npe_arg(cm, igl::ColorMapType)
npe_arg(f, T)


npe_begin_code()

  T & r;
  T & g;
  T & b;
  igl::colormap(cm, f, r, g, b);
  return std::make_tuple(npe::move(r), npe::move(g), npe::move(b));

npe_end_code()
#include <igl/colormap.h>

const char* ds_colormap = R"igl_Qu8mg5v7(

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

 Inputs:
      palette  256 by 3 array of color values
)igl_Qu8mg5v7";

npe_function(colormap)
npe_doc(ds_colormap)

npe_arg(palette, double [256][3])
npe_arg(x_in, T)


npe_begin_code()

  T & r;
  T & g;
  T & b;
  igl::colormap(palette, x_in, r, g, b);
  return std::make_tuple(npe::move(r), npe::move(g), npe::move(b));

npe_end_code()
#include <igl/colormap.h>

const char* ds_colormap = R"igl_Qu8mg5v7(

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

 Inputs:
     min_z  value at "0"
     max_z  value at "1"
)igl_Qu8mg5v7";

npe_function(colormap)
npe_doc(ds_colormap)

npe_arg(cm, igl::ColorMapType)
npe_arg(z, dense_f32, dense_f64)
npe_arg(min_z, double)
npe_arg(max_z, double)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  igl::colormap(cm, z, min_z, max_z, c);
  return npe::move(c);

npe_end_code()


