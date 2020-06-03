#include <npe.h>
#include <typedefs.h>






#include <igl/writeSTL.h>

const char* ds_write_stl = R"igl_Qu8mg5v7(

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

 Write a mesh to an stl file.
  
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
   Inputs:
     filename path to .obj file
     V  double matrix of vertex positions  #F*3 by 3
     F  index matrix of triangle indices #F by 3
     N  double matrix of vertex positions  #F by 3
     asci  write ascii file {true}
   Returns true on success, false on errors
  
)igl_Qu8mg5v7";

npe_function(write_stl)
npe_doc(ds_write_stl)

npe_arg(filename, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(n, dense_float, dense_double)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writeSTL(filename, v, f, n, ascii);
  return ;

npe_end_code()
#include <igl/writeSTL.h>

const char* ds_write_stl = R"igl_Qu8mg5v7(
See writeSTL for the documentation.
)igl_Qu8mg5v7";

npe_function(write_stl)
npe_doc(ds_write_stl)

npe_arg(filename, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writeSTL(filename, v, f, ascii);
  return ;

npe_end_code()


