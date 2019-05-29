#include <npe.h>
#include <typedefs.h>
#include <igl/bone_parents.h>

const char* ds_bone_parents = R"igl_Qu8mg5v7(
BONE_PARENTS Recover "parent" bones from directed graph representation.
Parameters
----------
BE  #BE by 2 list of directed bone edges

Returns
-------
P  #BE by 1 list of parent indices into BE, -1 means root.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(bone_parents)
npe_doc(ds_bone_parents)

npe_arg(be, dense_int, dense_longlong)


npe_begin_code()
  npe_Matrix_be p;
  igl::bone_parents(be, p);
  return npe::move(p);

npe_end_code()


