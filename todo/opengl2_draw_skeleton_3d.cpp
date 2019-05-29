#include <npe.h>
#include <typedefs.h>
#include <igl/draw_skeleton_3d.h>

const char* ds_draw_skeleton_3d = R"igl_Qu8mg5v7(

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

 Default color
)igl_Qu8mg5v7";

npe_function(draw_skeleton_3d)
npe_doc(ds_draw_skeleton_3d)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)


npe_begin_code()

  igl::  opengl2::draw_skeleton_3d(c, be, t);
  return ;

npe_end_code()
#include <igl/draw_skeleton_3d.h>

const char* ds_draw_skeleton_3d = R"igl_Qu8mg5v7(
See draw_skeleton_3d for the documentation.
)igl_Qu8mg5v7";

npe_function(draw_skeleton_3d)
npe_doc(ds_draw_skeleton_3d)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_float, dense_double)


npe_begin_code()

  igl::  opengl2::draw_skeleton_3d(c, be);
  return ;

npe_end_code()






#include <igl/draw_skeleton_3d.h>

const char* ds_draw_skeleton_3d = R"igl_Qu8mg5v7(

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

 Draw a skeleton
    
     Inputs:
       C  #C by dim List of joint rest positions
       BE  #BE by 2 list of bone edge indices into C
       T  #BE*(dim+1) by dim  matrix of stacked transposed bone transformations
       color  #BE|1 by 4 list of color
       half_bbd  half bounding box diagonal to determine scaling {1.0}
)igl_Qu8mg5v7";

npe_function(draw_skeleton_3d)
npe_doc(ds_draw_skeleton_3d)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)
npe_arg(color, dense_float, dense_double)
npe_arg(half_bbd, double)


npe_begin_code()

  igl::  opengl2::draw_skeleton_3d(c, be, t, color, half_bbd);
  return ;

npe_end_code()


