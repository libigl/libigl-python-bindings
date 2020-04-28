#include <npe.h>
#include <typedefs.h>
#include <igl/sort_angles.h>

const char* ds_sort_angles = R"igl_Qu8mg5v7(

Parameters
---------
M: m by n matrix of scalars. (n >= 2).  Assuming the first column of M
    contains values for y, and the second column is x.  Using the rest
    of the columns as tie-breaker.

Returns
-------
R: an array of m indices.  M.row(R[i]) contains the i-th smallest
    angle.

See also
--------


Notes
-----
Sort angles in ascending order in a numerically robust way.
Instead of computing angles using atan2(y, x), sort directly on (y, x).


Examples
--------

)igl_Qu8mg5v7";

npe_function(sort_angles)
npe_doc(ds_sort_angles)

npe_arg(m, dense_double)

npe_begin_code()

  EigenDense<npe_Scalar_v> r;
  igl::sort_angles(m, r);
  return npe::move(r);

npe_end_code()


