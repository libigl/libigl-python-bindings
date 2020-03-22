// TODO: __example __miss

#include <npe.h>
#include <typedefs.h>






#include <igl/intersect.h>

const char* ds_intersect = R"igl_Qu8mg5v7(

Determine the intersect between two sets of coefficients using ==

Parameters
----------
A  matrix of coefficients
B  matrix of coefficients


Returns
-------
C  matrix of elements appearing in both A and B, C is always resized to
      have a single column


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(intersect)
npe_doc(ds_intersect)

npe_arg(a, dense_int, dense_long)
npe_arg(b, npe_matches(a))


npe_begin_code()

  // TODO: remove __copy
  Eigen::Matrix<int, Eigen::Dynamic, 1, Eigen::ColMajor, Eigen::Dynamic, 1> a_copy = a.template cast<int>();
  Eigen::Matrix<int, Eigen::Dynamic, 1, Eigen::ColMajor, Eigen::Dynamic, 1> b_copy = b.template cast<int>();
  auto res = igl::intersect(a_copy, b_copy);
  return npe::move(res);

npe_end_code()


