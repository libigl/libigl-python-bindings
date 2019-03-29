#include <npe.h>
#include <typedefs.h>






#include <igl/write_triangle_mesh.h>

const char* ds_write_triangle_mesh = R"igl_Qu8mg5v7(

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

 write mesh to a file with automatic detection of file format.  supported:
   obj, off, stl, wrl, ply, mesh). 
   
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
     Index  type for indices (will be read as int and cast to Index)
   Inputs:
     str  path to file
     V  eigen double matrix #V by 3
     F  eigen int matrix #F by 3
     force_ascii  force ascii format even if binary is available 
   Returns true iff success
)igl_Qu8mg5v7";

npe_function(write_triangle_mesh)
npe_doc(ds_write_triangle_mesh)

npe_arg(str, std::string)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(force_ascii, bool)


npe_begin_code()

  igl::write_triangle_mesh(str, v, f, force_ascii);
  return ;

npe_end_code()


