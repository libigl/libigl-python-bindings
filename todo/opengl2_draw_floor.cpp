#include <npe.h>
#include <typedefs.h>






#include <igl/draw_floor.h>

const char* ds_draw_floor = R"igl_Qu8mg5v7(

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

 Draw a checkerboard floor aligned with current (X,Z) plane using ../opengl/OpenGL_
     calls. side=50 centered at (0,0):
       (-25,-25)-->(-25,25)-->(25,25)-->(25,-25)
    
     Use glPushMatrix(), glScaled(), glTranslated() to arrange the floor.
     
     Inputs:
       colorA  float4 color
       colorB  float4 color
    
     Example:
        Draw a nice floor
       glPushMatrix();
       glCullFace(GL_BACK);
       glEnable(GL_CULL_FACE);
       glEnable(GL_LIGHTING);
       glTranslated(0,-1,0);
       if(project(Vector3d(0,0,0))(2) - project(Vector3d(0,1,0))(2) > -FLOAT_EPS)
       {
         draw_floor_outline();
       }
       draw_floor();
       glPopMatrix();
       glDisable(GL_CULL_FACE);
    
)igl_Qu8mg5v7";

npe_function(draw_floor)
npe_doc(ds_draw_floor)

npe_arg(color_a, float *)
npe_arg(color_b, float *)
npe_arg(grid_size_x, int)
npe_arg(grid_size_y, int)


npe_begin_code()

  igl::  opengl2::draw_floor(color_a, color_b, grid_size_x, grid_size_y);
  return ;

npe_end_code()
#include <igl/draw_floor_outline.h>

const char* ds_draw_floor_outline = R"igl_Qu8mg5v7(
See draw_floor_outline for the documentation.
)igl_Qu8mg5v7";

npe_function(draw_floor_outline)
npe_doc(ds_draw_floor_outline)

npe_arg(color_a, float *)
npe_arg(color_b, float *)
npe_arg(grid_size_x, int)
npe_arg(grid_size_y, int)


npe_begin_code()

  igl::  opengl2::draw_floor_outline(color_a, color_b, grid_size_x, grid_size_y);
  return ;

npe_end_code()


