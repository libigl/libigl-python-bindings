#include <npe.h>
#include <typedefs.h>
#include <igl/line_field_missmatch.h>

const char* ds_line_field_missmatch = R"igl_Qu8mg5v7(

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

 Inputs:
     V         #V by 3 eigen Matrix of mesh vertex 3D positions
     F         #F by 3 eigen Matrix of face (quad) indices
     PD1       #F by 3 eigen Matrix of the first per face cross field vector
     PD2       #F by 3 eigen Matrix of the second per face cross field vector
     isCombed  boolean, specifying whether the field is combed (i.e. matching has been precomputed.
               If not, the field is combed first.
   Output:
     Handle_MMatch    #F by 3 eigen Matrix containing the integer missmatch of the cross field
                      across all face edges
  
)igl_Qu8mg5v7";

npe_function(line_field_missmatch)
npe_doc(ds_line_field_missmatch)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1, dense_float, dense_double)
npe_arg(is_combed, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> missmatch;
  igl::line_field_missmatch(v, f, pd1, is_combed, missmatch);
  return npe::move(missmatch);

npe_end_code()


