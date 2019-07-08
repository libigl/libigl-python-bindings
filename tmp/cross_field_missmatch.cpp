// TODO: Maybe need more templates in libigl or ways to wrap around output params

#include <npe.h>
#include <typedefs.h>
#include <igl/cross_field_mismatch.h>

const char* ds_cross_field_mismatch = R"igl_Qu8mg5v7(

Parameters
----------
V         #V by 3 eigen Matrix of mesh vertex 3D positions
F         #F by 3 eigen Matrix of face (quad) indices
PD1       #F by 3 eigen Matrix of the first per face cross field vector
PD2       #F by 3 eigen Matrix of the second per face cross field vector
isCombed  boolean, specifying whether the field is combed (i.e. matching has been precomputed.
          If not, the field is combed first.


Returns
-------
Handle_MMatch    #F by 3 eigen Matrix containing the integer mismatch of the cross field
                 across all face edges


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(cross_field_mismatch)
npe_doc(ds_cross_field_mismatch)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))
npe_arg(is_combed, bool)


npe_begin_code()

  npe_Matrix_f mismatch;
  igl::cross_field_mismatch(v, f, pd1, pd2, is_combed, mismatch);
  return npe::move(mismatch);

npe_end_code()


