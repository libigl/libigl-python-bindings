#include <npe.h>
#include <typedefs.h>
#include <igl/rigid_alignment.h>

const char* ds_rigid_alignment = R"igl_Qu8mg5v7(

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

 Find the rigid transformation that best aligns the 3D points X to their
   corresponding points P with associated normals N.
  
    min       ‖(X*R+t-P)'N‖²
    R∈SO(3)
    t∈R³
  
   Inputs:
     X  #X by 3 list of query points
     P  #X by 3 list of corresponding (e.g., closest) points
     N  #X by 3 list of unit normals for each row in P
   Outputs:
     R  3 by 3 rotation matrix
     t  1 by 3 translation vector
  
     See also: icp
)igl_Qu8mg5v7";

npe_function(rigid_alignment)
npe_doc(ds_rigid_alignment)

npe_arg(x, dense_f32, dense_f64)
npe_arg(p, dense_f32, dense_f64)
npe_arg(n, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::rigid_alignment(x, p, n, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


