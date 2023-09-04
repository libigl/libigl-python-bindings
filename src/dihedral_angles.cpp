// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/dihedral_angles.h>

const char* ds_dihedral_angles = R"igl_Qu8mg5v7(
Compute dihedral angles for all tets of a given tet mesh (v, t).

Parameters
----------
v : #v by 3 list of vertex positions
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
npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_int32, dense_int64)

npe_begin_code()
  assert_valid_tet_mesh(v, t);
  EigenDenseLike<npe_Matrix_v> theta;
  EigenDenseLike<npe_Matrix_v> cos_theta;
  igl::dihedral_angles(v, t, theta, cos_theta);
  return std::make_tuple(npe::move(theta), npe::move(cos_theta));

npe_end_code()


const char* ds_dihedral_angles_intrinsic = R"igl_Qu8mg5v7(
See dihedral_angles for the documentation.
)igl_Qu8mg5v7";

npe_function(dihedral_angles_intrinsic)
npe_doc(ds_dihedral_angles_intrinsic)
npe_arg(l, dense_float, dense_double)
npe_arg(a, npe_matches(l))

npe_begin_code()

  EigenDenseLike<npe_Matrix_l> theta;
  EigenDenseLike<npe_Matrix_l> cos_theta;
  igl::dihedral_angles_intrinsic(l, a, theta, cos_theta);
  return std::make_tuple(npe::move(theta), npe::move(cos_theta));

npe_end_code()


