#include <npe.h>
#include <typedefs.h>
#include <igl/uniform_type_to_string.h>

const char* ds_uniform_type_to_string = R"igl_Qu8mg5v7(

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

 Convert a GL uniform variable type (say, returned from
     glGetActiveUniform) and output a string naming that type
     Inputs:
       type  enum for given type
     Returns string name of that type
)igl_Qu8mg5v7";

npe_function(uniform_type_to_string)
npe_doc(ds_uniform_type_to_string)

npe_arg(type, int)


npe_begin_code()

  igl::  opengl::uniform_type_to_string(type);
  return ;

npe_end_code()


