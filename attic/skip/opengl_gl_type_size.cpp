#include <npe.h>
#include <typedefs.h>
#include <igl/gl_type_size.h>

const char* ds_gl_type_size = R"igl_Qu8mg5v7(

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

 Return the number of bytes for a given OpenGL type  Inputs:
       type  enum value of opengl type
     Returns size in bytes of type
)igl_Qu8mg5v7";

npe_function(gl_type_size)
npe_doc(ds_gl_type_size)

npe_arg(type, int)


npe_begin_code()

  igl::  opengl::gl_type_size(type);
  return ;

npe_end_code()


