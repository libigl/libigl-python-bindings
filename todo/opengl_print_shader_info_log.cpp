#include <npe.h>
#include <typedefs.h>
#include <igl/print_shader_info_log.h>

const char* ds_print_shader_info_log = R"igl_Qu8mg5v7(

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
       obj  OpenGL index of shader to print info log about
)igl_Qu8mg5v7";

npe_function(print_shader_info_log)
npe_doc(ds_print_shader_info_log)

npe_arg(obj, int)


npe_begin_code()

  igl::  opengl::print_shader_info_log(obj);
  return ;

npe_end_code()


