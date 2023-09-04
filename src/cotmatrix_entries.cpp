// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/cotmatrix_entries.h>

const char* ds_cotmatrix_entries = R"igl_Qu8mg5v7(

COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)

Parameters
----------
V  #V by dim list of rest domain positions
F  #F by {3|4} list of {triangle|tetrahedra} indices into V


Returns
-------
  C  #F by 3 list of 1/2*cotangents corresponding angles
    for triangles, columns correspond to edges [1,2],[2,0],[0,1]
OR
  C  #F by 6 list of 1/6*cotangents of dihedral angles*edge lengths
    for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2]


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(cotmatrix_entries)
npe_doc(ds_cotmatrix_entries)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenDenseLike<npe_Matrix_v> c;
  igl::cotmatrix_entries(v, f, c);
  return npe::move(c);

npe_end_code()


