#include <npe.h>
#include <typedefs.h>






#include <igl/print_gl_get.h>

const char* ds_print_gl_get = R"igl_Qu8mg5v7(

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

 Prints the value of pname found by issuing glGet*(pname,*)
     Inputs:
       pname  enum key to gl parameter
)igl_Qu8mg5v7";

npe_function(print_gl_get)
npe_doc(ds_print_gl_get)



npe_begin_code()

  GLenum pname;
  igl::  opengl2::print_gl_get(pname);
  return npe::move(pname);

npe_end_code()


