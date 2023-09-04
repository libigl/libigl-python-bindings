// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/vector_area_matrix.h>

const char* ds_vector_area_matrix = R"igl_Qu8mg5v7(
Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *
   [V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).
Parameters
----------
f : #f by 3 array of mesh faces (must be triangles)

Returns
-------
a : #vx2 by #vx2 area matrix

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(vector_area_matrix)
npe_doc(ds_vector_area_matrix)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  Eigen::SparseMatrix<double> a;
  igl::vector_area_matrix(f, a);
  return npe::move(a);

npe_end_code()


