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
#include <igl/project_isometrically_to_plane.h>

const char *ds_project_isometrically_to_plane = R"igl_Qu8mg5v7(
 Project each triangle to the plane

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of mesh indices

Returns
-------
U  #F*3 by 2 list of triangle positions
UF  #F by 3 list of mesh indices into U
I  #V by #F*3 such that I(i,j) = 1 implies U(j,:) corresponds to V(i,:)

See also
--------


Notes
-----
None

Examples
--------
   [U,UF,I] = project_isometrically_to_plane(V,F)

)igl_Qu8mg5v7";

npe_function(project_isometrically_to_plane)
npe_doc(ds_project_isometrically_to_plane)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  EigenDense<npe_Scalar_v> u;
  EigenDense<npe_Scalar_f> uf;
  Eigen::SparseMatrix < npe_Scalar_f> i;
  igl::project_isometrically_to_plane(v, f, u, uf, i);
  return std::make_tuple(npe::move(u), npe::move(uf), npe::move(i));

npe_end_code()


