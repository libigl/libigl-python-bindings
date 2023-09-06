// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/isolines.h>

const char *ds_isolines = R"igl_Qu8mg5v7(
 Constructs isolines for a function z given on a mesh (V,F)

Parameters
----------
  V  #V by dim list of mesh vertex positions
  F  #F by 3 list of mesh triangle indices into V
  S  #S by 1 list of per-vertex scalar values
  vals  #vals by 1 list of values to compute isolines for

Returns
-------
   iV  #iV by dim list of isoline vertex positions
   iE  #iE by 2 list of edge indices into iV
   I  #iE by 1 list of indices into vals indicating which value

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(isolines)
npe_doc(ds_isolines)

npe_arg(V, dense_float, dense_double)
npe_arg(F, dense_int32, dense_int64)
npe_arg(S, npe_matches(V))
npe_arg(vals, npe_matches(S))


npe_begin_code()

  assert_valid_23d_tri_mesh(V, F);
  assert_rows_match(V, S, "V", "S");
  assert_cols_equals(S, 1, "S");
  EigenDenseLike<npe_Matrix_V> iV;
  EigenDenseLike<npe_Matrix_F> iE;
  Eigen::Matrix<typename npe_Matrix_F::Scalar, Eigen::Dynamic, 1> I;
  Eigen::Matrix<typename npe_Matrix_vals::Scalar, Eigen::Dynamic, 1> vals_copy = vals;
  igl::isolines(V, F, S.col(0), vals_copy, iV, iE, I);
  return std::make_tuple(npe::move(iV), npe::move(iE), npe::move(I));

npe_end_code()


