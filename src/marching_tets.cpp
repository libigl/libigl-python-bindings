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
#include <igl/marching_tets.h>

const char *ds_marching_tets = R"igl_Qu8mg5v7(
Performs the marching tetrahedra algorithm on a tet mesh defined by TV and
TT with scalar values defined at each vertex in TV. The output is a
triangle mesh approximating the isosurface coresponding to the value
isovalue.

Parameters
----------
TV  #tet_vertices x 3 array -- The vertices of the tetrahedral mesh
TT  #tets x 4 array --  The indexes of each tet in the tetrahedral mesh
S  #tet_vertices x 1 array -- The values defined on each tet vertex
isovalue  scalar -- The isovalue of the level set we want to compute

Returns
-------
SV : #SV x 3 array -- The vertices of the output level surface mesh
SF : #SF x 3 array -- The face indexes of the output level surface mesh
J : #SF list of indices into TT revealing which tet each face comes from
BC : #SV x #TV list of barycentric coordinates so that SV = BC*TV

See also
--------


Notes
-----
None

Examples
--------
sv, sf, j, bc = igl.marching_tets(tv, tt, s, isovalue)

)igl_Qu8mg5v7";

npe_function(marching_tets)
npe_doc(ds_marching_tets)

npe_arg(TV, dense_float, dense_double)
npe_arg(TT, dense_int32, dense_int64)
npe_arg(S, npe_matches(TV))
npe_arg(isovalue, double)

npe_begin_code()
  assert_valid_tet_mesh(TV, TT, "TV", "TT");
  assert_rows_match(TV, S, "TV", "S");
  assert_cols_equals(S, 1, "S");

  EigenDenseLike<npe_Matrix_TV> SV;
  EigenDenseLike<npe_Matrix_TT> SF;
  Eigen::Matrix<typename npe_Matrix_TT::Scalar, Eigen::Dynamic, 1> J;
  EigenSparseLike<npe_Matrix_TV> BC;
  igl::marching_tets(TV, TT, S, isovalue, SV, SF, J, BC);
  return std::make_tuple(npe::move(SV), npe::move(SF), npe::move(J), npe::move(BC));

npe_end_code()
