#include <npe.h>
#include <typedefs.h>






#include <igl/create_shader_program.h>

const char* ds_create_shader_program = R"igl_Qu8mg5v7(

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

 Create a shader program with a vertex and fragments shader loading from
     source strings and vertex attributes assigned from a map before linking the
     shaders to the program, making it ready to use with glUseProgram(id)
     Inputs:
       geom_source  string containing source code of geometry shader (can be
         "" to mean use default pass-through)
       vert_source  string containing source code of vertex shader
       frag_source  string containing source code of fragment shader
       attrib  map containing table of vertex attribute strings add their
       correspondingly ids (generated previously using glBindAttribLocation)
     Outputs:
       id  index id of created shader, set to 0 on error
     Returns true on success, false on error
    
     Note: Caller is responsible for making sure that current value of id is not
     leaking a shader (since it will be overwritten)
    
     See also: destroy_shader_program
)igl_Qu8mg5v7";

npe_function(create_shader_program)
npe_doc(ds_create_shader_program)

npe_arg(geom_source, std::string &)
npe_arg(vert_source, std::string &)
npe_arg(frag_source, std::string &)
npe_arg(attrib, int &)


npe_begin_code()

  int & id;
  igl::  opengl::create_shader_program(geom_source, vert_source, frag_source, attrib, id);
  return npe::move(id);

npe_end_code()
#include <igl/create_shader_program.h>

const char* ds_create_shader_program = R"igl_Qu8mg5v7(
See create_shader_program for the documentation.
)igl_Qu8mg5v7";

npe_function(create_shader_program)
npe_doc(ds_create_shader_program)

npe_arg(vert_source, std::string &)
npe_arg(frag_source, std::string &)
npe_arg(attrib, int &)


npe_begin_code()

  int & id;
  igl::  opengl::create_shader_program(vert_source, frag_source, attrib, id);
  return npe::move(id);

npe_end_code()


