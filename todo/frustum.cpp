#include <npe.h>
#include <typedefs.h>






#include <igl/frustum.h>

const char* ds_frustum = R"igl_Qu8mg5v7(

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

 Implementation of the deprecated glFrustum function.
  
   Inputs:
     left  coordinate of left vertical clipping plane
     right  coordinate of right vertical clipping plane
     bottom  coordinate of bottom vertical clipping plane
     top  coordinate of top vertical clipping plane
     nearVal  distance to near plane
     farVal  distance to far plane
   Outputs:
     P  4x4 perspective matrix
)igl_Qu8mg5v7";

npe_function(frustum)
npe_doc(ds_frustum)

npe_arg(left, typename DerivedP::Scalar)
npe_arg(right, typename DerivedP::Scalar)
npe_arg(bottom, typename DerivedP::Scalar)
npe_arg(top, typename DerivedP::Scalar)
npe_arg(near_val, typename DerivedP::Scalar)
npe_arg(far_val, typename DerivedP::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::frustum(left, right, bottom, top, near_val, far_val, p);
  return npe::move(p);

npe_end_code()


