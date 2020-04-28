#include <npe.h>
#include <typedefs.h>






#include <igl/writeWRL.h>

const char* ds_write_wrl = R"igl_Qu8mg5v7(

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

 Write mesh to a .wrl file
  
   Inputs:
     str  path to .wrl file
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices
   Returns true iff succes
)igl_Qu8mg5v7";

npe_function(write_wrl)
npe_doc(ds_write_wrl)

npe_arg(str, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  igl::writeWRL(str, v, f);
  return ;

npe_end_code()
#include <igl/writeWRL.h>

const char* ds_write_wrl = R"igl_Qu8mg5v7(

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

 Write mesh to a .wrl file
  
   Inputs:
     str  path to .wrl file
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices
     C  double matrix of rgb values per vertex #V by 3
   Returns true iff succes
)igl_Qu8mg5v7";

npe_function(write_wrl)
npe_doc(ds_write_wrl)

npe_arg(str, std::string &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(c, dense_float, dense_double)


npe_begin_code()

  igl::writeWRL(str, v, f, c);
  return ;

npe_end_code()


