#include <npe.h>
#include <typedefs.h>
#include <igl/dihedral_angles.h>

const char* ds_dihedral_angles = R"igl_Qu8mg5v7(

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

 DIHEDRAL_ANGLES Compute dihedral angles for all tets of a given tet mesh
   (V,T)
  
   theta = dihedral_angles(V,T)
   theta = dihedral_angles(V,T,'ParameterName',parameter_value,...)
  
   Inputs:
     V  #V by dim list of vertex positions
     T  #V by 4 list of tet indices
   Outputs:
     theta  #T by 6 list of dihedral angles (in radians)
     cos_theta  #T by 6 list of cosine of dihedral angles (in radians)
  
)igl_Qu8mg5v7";

npe_function(dihedral_angles)
npe_doc(ds_dihedral_angles)



npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> t;
  EigenDense<npe_Scalar_> theta;
  EigenDense<npe_Scalar_> cos_theta;
  igl::dihedral_angles(v, t, theta, cos_theta);
  return std::make_tuple(npe::move(v), npe::move(t), npe::move(theta), npe::move(cos_theta));

npe_end_code()
#include <igl/dihedral_angles_intrinsic.h>

const char* ds_dihedral_angles_intrinsic = R"igl_Qu8mg5v7(
See dihedral_angles_intrinsic for the documentation.
)igl_Qu8mg5v7";

npe_function(dihedral_angles_intrinsic)
npe_doc(ds_dihedral_angles_intrinsic)



npe_begin_code()

  EigenDense<npe_Scalar_> l;
  EigenDense<npe_Scalar_> a;
  EigenDense<npe_Scalar_> theta;
  EigenDense<npe_Scalar_> cos_theta;
  igl::dihedral_angles_intrinsic(l, a, theta, cos_theta);
  return std::make_tuple(npe::move(l), npe::move(a), npe::move(theta), npe::move(cos_theta));

npe_end_code()


