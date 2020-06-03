#include <npe.h>
#include <typedefs.h>






#include <igl/invert_diag.h>

const char* ds_invert_diag = R"igl_Qu8mg5v7(

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

 Templates:
     T  should be a eigen sparse matrix primitive type like int or double
   Inputs:
     X  an m by n sparse matrix
   Outputs:
     Y  an m by n sparse matrix
)igl_Qu8mg5v7";

npe_function(invert_diag)
npe_doc(ds_invert_diag)

npe_arg(x, Eigen::SparseMatrixBase<T> &)


npe_begin_code()

  sparse_double y;
  igl::invert_diag(x, y);
  return npe::move(y);

npe_end_code()


