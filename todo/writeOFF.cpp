#include <npe.h>
#include <typedefs.h>






#include <igl/writeOFF.h>

const char* ds_write_off = R"igl_Qu8mg5v7(

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

Export geometry and colors-by-vertex
   Export a mesh from an ascii OFF file, filling in vertex positions.
   Only triangle meshes are supported
  
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
     Index  type for indices (will be read as int and cast to Index)
   Inputs:
    str  path to .off output file
     V  #V by 3 mesh vertex positions
     F  #F by 3 mesh indices into V
     C  double matrix of rgb values per vertex #V by 3
   Outputs:
   Returns true on success, false on errors
)igl_Qu8mg5v7";

npe_function(write_off)
npe_doc(ds_write_off)

npe_arg(str, std::string)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(c, dense_f32, dense_f64)


npe_begin_code()

  igl::writeOFF(str, v, f, c);
  return ;

npe_end_code()
#include <igl/writeOFF.h>

const char* ds_write_off = R"igl_Qu8mg5v7(
See writeOFF for the documentation.
)igl_Qu8mg5v7";

npe_function(write_off)
npe_doc(ds_write_off)

npe_arg(str, std::string)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  igl::writeOFF(str, v, f);
  return ;

npe_end_code()


