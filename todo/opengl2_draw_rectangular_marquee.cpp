#include <npe.h>
#include <typedefs.h>
#include <igl/draw_rectangular_marquee.h>

const char* ds_draw_rectangular_marquee = R"igl_Qu8mg5v7(

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

 Draw a rectangular marquee (selection box) in screen space. This sets up
     screen space using current viewport.
    
     Inputs:
       from_x  x coordinate of from point
       from_y  y coordinate of from point
       to_x  x coordinate of to point
       to_y  y coordinate of to point
)igl_Qu8mg5v7";

npe_function(draw_rectangular_marquee)
npe_doc(ds_draw_rectangular_marquee)

npe_arg(from_x, int)
npe_arg(from_y, int)
npe_arg(to_x, int)
npe_arg(to_y, int)


npe_begin_code()

  igl::  opengl2::draw_rectangular_marquee(from_x, from_y, to_x, to_y);
  return ;

npe_end_code()


