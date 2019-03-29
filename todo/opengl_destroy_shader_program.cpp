#include <npe.h>
#include <typedefs.h>
#include <igl/destroy_shader_program.h>

const char* ds_destroy_shader_program = R"igl_Qu8mg5v7(

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

 Properly destroy a shader program. Detach and delete each of its shaders
     and delete it
     Inputs:
       id  index id of created shader, set to 0 on error
     Returns true on success, false on error
     
     Note: caller is responsible for making sure he doesn't foolishly continue
     to use id as if it still contains a program
     
     See also: create_shader_program
)igl_Qu8mg5v7";

npe_function(destroy_shader_program)
npe_doc(ds_destroy_shader_program)

npe_arg(id, int)


npe_begin_code()

  igl::  opengl::destroy_shader_program(id);
  return ;

npe_end_code()


