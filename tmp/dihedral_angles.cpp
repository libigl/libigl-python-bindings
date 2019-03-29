#include <npe.h>
#include <typedefs.h>
#include <igl/dihedral_angles.h>

const char* ds_dihedral_angles = R"igl_Qu8mg5v7(
Compute dihedral angles for all tets of a given tet mesh (v, t).

Parameters
----------
v : #v by dim list of vertex positions
t : #v by 4 list of tet indices

Returns
-------
theta : #t by 6 list of dihedral angles (in radians)
cos_theta : #t by 6 list of cosine of dihedral angles (in radians)

See also
--------


Notes
-----
None

Examples
--------
# TetMesh in (v, t)
>>> theta, cos_theta = dihedral_angles(v, t)
)igl_Qu8mg5v7";

npe_function(dihedral_angles)
npe_doc(ds_dihedral_angles)
npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_i32, dense_i64)

npe_begin_code()

  npe_Matrix_v theta;
  npe_Matrix_v cos_theta;
  igl::dihedral_angles(v, t, theta, cos_theta);
  return std::make_tuple(npe::move(theta), npe::move(cos_theta));

npe_end_code()


const char* ds_dihedral_angles_intrinsic = R"igl_Qu8mg5v7(
See dihedral_angles for the documentation.
)igl_Qu8mg5v7";

npe_function(dihedral_angles_intrinsic)
npe_doc(ds_dihedral_angles_intrinsic)
npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_i32, dense_i64)

npe_begin_code()

  npe_Matrix_v theta;
  npe_Matrix_v cos_theta;
  igl::dihedral_angles_intrinsic(v, t, theta, cos_theta);
  return std::make_tuple(npe::move(theta), npe::move(cos_theta));

npe_end_code()


