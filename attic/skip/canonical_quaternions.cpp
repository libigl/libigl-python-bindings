// TODO: __bug


#include <npe.h>
#include <typedefs.h>
#include <igl/canonical_quaternions.h>

const char* ds_canonical_quaternions_float = R"igl_Qu8mg5v7(

Return element [i][j] of the corresponding CANONICAL_VIEW_QUAT_* of the

Parameters
----------
i  index of quaternion
j  index of coordinate in quaternion i


Returns
-------
Returns values of CANONICAL_VIEW_QUAT<float>(i, j)

See also
--------

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";


npe_function(canonical_quaternions)
npe_doc(ds_canonical_quaternions)


npe_begin_code()

  int i;
  int j;
  return igl::CANONICAL_VIEW_QUAT<float>(i, j);
  //return std::make_tuple(npe::move(i), npe::move(j));

npe_end_code()



const char* ds_canonical_quaternions_double = R"igl_Qu8mg5v7(

Template specializations for float and double

Parameters
----------


Returns
-------
Returns values of CANONICAL_VIEW_QUAT<double>(i, j)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(canonical_quaternions)
npe_doc(ds_canonical_quaternions)


npe_begin_code()

  int i;
  int j;
  return igl::CANONICAL_VIEW_QUAT<double>(i, j);
  //return std::make_tuple(npe::move(i), npe::move(j));

npe_end_code()

