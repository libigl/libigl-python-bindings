#include <npe.h>
#include <typedefs.h>
#include <igl/sort_angles.h>

const char* ds_sort_angles = R"igl_Qu8mg5v7(

Sort angles in ascending order in a numerically robust way.
Instead of computing angles using atan2(y, x), sort directly on (y, x).
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
None.

Examples
--------

)igl_Qu8mg5v7";

npe_function(sort_angles)
npe_doc(ds_sort_angles)

npe_arg(m, dense_float, dense_double)

npe_begin_code()

  // In the libigl code r is column major, and using row major fails assertion
  // EIGEN_STATIC_ASSERT((EIGEN_IMPLIES(MaxRowsAtCompileTime==1 && 
  //    MaxColsAtCompileTime!=1, (Options&RowMajor)==RowMajor)
  Eigen::Matrix<int, Eigen::Dynamic, 1, Eigen::ColMajor, Eigen::Dynamic, 1> r;
  igl::sort_angles(m, r);
  return npe::move(r);

npe_end_code()


