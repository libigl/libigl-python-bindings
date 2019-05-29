#include <npe.h>
#include <typedefs.h>






#include <igl/writePLY.h>

const char* ds_write_ply = R"igl_Qu8mg5v7(

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

 Write a mesh to a .ply file. 
  
   Inputs:
     filename  path to .ply file
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices
     N  #V by 3 list of vertex normals
     UV  #V by 2 list of vertex texture coordinates
   Returns true iff success
)igl_Qu8mg5v7";

npe_function(write_ply)
npe_doc(ds_write_ply)

npe_arg(filename, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(n, dense_float, dense_double)
npe_arg(uv, dense_float, dense_double)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writePLY(filename, v, f, n, uv, ascii);
  return ;

npe_end_code()
#include <igl/writePLY.h>

const char* ds_write_ply = R"igl_Qu8mg5v7(
See writePLY for the documentation.
)igl_Qu8mg5v7";

npe_function(write_ply)
npe_doc(ds_write_ply)

npe_arg(filename, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writePLY(filename, v, f, ascii);
  return ;

npe_end_code()


