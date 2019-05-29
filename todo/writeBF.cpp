#include <npe.h>
#include <typedefs.h>






#include <igl/writeBF.h>

const char* ds_write_bf = R"igl_Qu8mg5v7(

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

 Write a bones forest to a file
  
   Input:
     file_name  path to .bf bones tree file
     WI  #B list of unique weight indices
     P  #B list of parent indices into B, -1 for roots
     O  #B list of tip offsets
   Returns true on success, false on errors
)igl_Qu8mg5v7";

npe_function(write_bf)
npe_doc(ds_write_bf)

npe_arg(filename, std::string &)
npe_arg(wi, dense_float, dense_double)
npe_arg(p, dense_float, dense_double)
npe_arg(o, dense_float, dense_double)


npe_begin_code()

  igl::writeBF(filename, wi, p, o);
  return ;

npe_end_code()


