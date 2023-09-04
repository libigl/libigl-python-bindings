// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/cotmatrix_intrinsic.h>

const char *ds_cotmatrix_intrinsic = R"igl_Qu8mg5v7(

Constructs the cotangent stiffness matrix (discrete laplacian) for a given
   mesh with faces F and edge lengths l.

Parameters
----------

l  #F by 3 list of (half-)edge lengths
F  #F by 3 list of face indices into some (not necessarily
  determined/embedable) list of vertex positions V. It is assumed #V ==
  F.maxCoeff()+1

Returns
-------

L  #V by #V sparse Laplacian matrix

See also
--------

cotmatrix, intrinsic_delaunay_cotmatrix

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(cotmatrix_intrinsic)
npe_doc(ds_cotmatrix_intrinsic)

npe_arg(l, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_rows_match(l, f, "l", "f");
  assert_cols_equals(l, 3, "l");
  assert_valid_tri_mesh_faces(f);

  Eigen::SparseMatrix<npe_Scalar_l> mat;
  igl::cotmatrix_intrinsic(l, f, mat);
  return npe::move(mat);

npe_end_code()


