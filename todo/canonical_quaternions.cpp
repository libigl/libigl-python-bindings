#include <npe.h>
#include <typedefs.h>
#include <igl/CANONICAL_VIEW_QUAT.h>

const char* ds_canonical_view_quat = R"igl_Qu8mg5v7(

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

 Return element [i][j] of the corresponding CANONICAL_VIEW_QUAT_* of the
   given templated type
   Inputs:
     i  index of quaternion
     j  index of coordinate in quaternion i
   Returns values of CANONICAL_VIEW_QUAT_*[i][j]
)igl_Qu8mg5v7";

npe_function(canonical_view_quat)
npe_doc(ds_canonical_view_quat)



npe_begin_code()

  int i;
  int j;
  igl::CANONICAL_VIEW_QUAT(i, j);
  return std::make_tuple(npe::move(i), npe::move(j));

npe_end_code()
#include <igl/CANONICAL_VIEW_QUAT.h>

const char* ds_canonical_view_quat = R"igl_Qu8mg5v7(

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

 Template specializations for float and double
)igl_Qu8mg5v7";

npe_function(canonical_view_quat)
npe_doc(ds_canonical_view_quat)



npe_begin_code()

  int i;
  int j;
  igl::CANONICAL_VIEW_QUAT(i, j);
  return std::make_tuple(npe::move(i), npe::move(j));

npe_end_code()
#include <igl/CANONICAL_VIEW_QUAT.h>

const char* ds_canonical_view_quat = R"igl_Qu8mg5v7(
See CANONICAL_VIEW_QUAT for the documentation.
)igl_Qu8mg5v7";

npe_function(canonical_view_quat)
npe_doc(ds_canonical_view_quat)



npe_begin_code()

  int i;
  int j;
  igl::CANONICAL_VIEW_QUAT(i, j);
  return std::make_tuple(npe::move(i), npe::move(j));

npe_end_code()


