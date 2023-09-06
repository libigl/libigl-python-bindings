// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// static assertion fail: YOU_MIXED_DIFFERENT_NUMERIC_TYPES__YOU_NEED_TO_USE_THE_CAST_METHOD_OF_MATRIXBASE_TO_CAST_NUMERIC_TYPES_EXPLICITLY

#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/crouzeix_raviart_massmatrix.h>

const char* ds_crouzeix_raviart_massmatrix = R"igl_Qu8mg5v7(

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where
  M(e,e) is just the sum of the areas of the triangles on either side of an
  edge e.

Parameters
----------
V  #V by dim list of vertex positions
F  #F by 3/4 list of triangle/tetrahedron indices

Returns
-------
M  #E by #E edge/face-based diagonal mass matrix
E  #E by 2/3 list of edges/faces
EMAP  #F*3/4 list of indices mapping allE to E

See also
--------
crouzeix_raviart_cotmatrix

Notes
-----
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
  Harmon, Zorin, Grinspun 2007]

Examples
--------


)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_massmatrix)
npe_doc(ds_crouzeix_raviart_massmatrix)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenSparseLike<npe_Matrix_v> m;
  EigenDenseLike<npe_Matrix_f> e;
  Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> emap;
  igl::crouzeix_raviart_massmatrix(v, f, m, e, emap);
  return std::make_tuple(npe::move(m), npe::move(e), npe::move(emap));

npe_end_code()



const char* ds_crouzeix_raviart_massmatrix_known_e = R"igl_Qu8mg5v7(

wrapper if E and EMAP are already computed (better match!)

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

)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_massmatrix_known_e)
npe_doc(ds_crouzeix_raviart_massmatrix_known_e)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(e, npe_matches(f))
npe_arg(emap, npe_matches(f))


npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  //assert_rows_equals(emap, 3/4*f.rows(), "emap");
  //assert_cols_equals(e, 2/3, "emap");
  assert_cols_equals(emap, 1, "emap");
  EigenSparseLike<npe_Matrix_v> m;
  igl::crouzeix_raviart_massmatrix(v, f, e, emap, m);
  return npe::move(m);

npe_end_code()


