#include <npe.h>
#include <typedefs.h>
#include <igl/draw_skeleton_vector_graphics.h>

const char* ds_draw_skeleton_vector_graphics = R"igl_Qu8mg5v7(
See draw_skeleton_vector_graphics for the documentation.
)igl_Qu8mg5v7";

npe_function(draw_skeleton_vector_graphics)
npe_doc(ds_draw_skeleton_vector_graphics)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)


npe_begin_code()

  igl::  opengl2::draw_skeleton_vector_graphics(c, be, t);
  return ;

npe_end_code()






#include <igl/draw_skeleton_vector_graphics.h>

const char* ds_draw_skeleton_vector_graphics = R"igl_Qu8mg5v7(

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

 Draw a skeleton with a 2D vector graphcis style à la BBW, STBS, Monotonic,
     FAST papers.
    
     Inputs:
       C  #C by dim list of joint positions
       BE #BE by 2 list of bone edge indices into C
      point_color  color of points
      line_color  color of lines
)igl_Qu8mg5v7";

npe_function(draw_skeleton_vector_graphics)
npe_doc(ds_draw_skeleton_vector_graphics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(point_color, float *)
npe_arg(line_color, float *)


npe_begin_code()

  igl::  opengl2::draw_skeleton_vector_graphics(c, be, point_color, line_color);
  return ;

npe_end_code()
#include <igl/draw_skeleton_vector_graphics.h>

const char* ds_draw_skeleton_vector_graphics = R"igl_Qu8mg5v7(

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

 Use default colors (originally from BBW paper)
)igl_Qu8mg5v7";

npe_function(draw_skeleton_vector_graphics)
npe_doc(ds_draw_skeleton_vector_graphics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)


npe_begin_code()

  igl::  opengl2::draw_skeleton_vector_graphics(c, be);
  return ;

npe_end_code()
#include <igl/draw_skeleton_vector_graphics.h>

const char* ds_draw_skeleton_vector_graphics = R"igl_Qu8mg5v7(

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

   T  #BE*(dim+1) by dim  matrix of stacked transposed bone transformations
)igl_Qu8mg5v7";

npe_function(draw_skeleton_vector_graphics)
npe_doc(ds_draw_skeleton_vector_graphics)

npe_arg(c, dense_float, dense_double)
npe_arg(be, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)
npe_arg(point_color, float *)
npe_arg(line_color, float *)


npe_begin_code()

  igl::  opengl2::draw_skeleton_vector_graphics(c, be, t, point_color, line_color);
  return ;

npe_end_code()


