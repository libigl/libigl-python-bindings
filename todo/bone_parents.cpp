#include <npe.h>
#include <typedefs.h>
#include <igl/bone_parents.h>

const char* ds_bone_parents = R"igl_Qu8mg5v7(

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

 BONE_PARENTS Recover "parent" bones from directed graph representation.
   
   Inputs:
     BE  #BE by 2 list of directed bone edges
   Outputs:
     P  #BE by 1 list of parent indices into BE, -1 means root.
  
)igl_Qu8mg5v7";

npe_function(bone_parents)
npe_doc(ds_bone_parents)

npe_arg(be, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::bone_parents(be, p);
  return npe::move(p);

npe_end_code()


