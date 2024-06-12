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
#include <igl/isolines_intrinsic.h>

const char *ds_isolines_intrinsic = R"igl_Qu8mg5v7(
 Constructs isolines interpolation parameters for a function z given on a mesh (V,F)

Parameters
----------
  F  #F by 3 list of mesh triangle indices into V
  S  #S by 1 list of per-vertex scalar values
  vals  #vals by 1 list of values to compute isolines for

Returns
-------
   iB  #iB by 3 list of barycentric coordinates
   iFI  #iB list of triangle indices for each row of iB
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

npe_function(isolines_intrinsic)
npe_doc(ds_isolines_intrinsic)

npe_arg(F, dense_int32, dense_int64)
npe_arg(S, dense_float, dense_double)
npe_arg(vals, npe_matches(S))


npe_begin_code()

  assert_cols_equals(S, 1, "S");
  Eigen::Matrix<typename npe_Matrix_S::Scalar, Eigen::Dynamic, 3> iB;
  Eigen::Matrix<int, Eigen::Dynamic, 1> iFI;
  EigenDenseLike<npe_Matrix_F> iE;
  Eigen::Matrix<typename npe_Matrix_F::Scalar, Eigen::Dynamic, 1> I;
  Eigen::Matrix<typename npe_Matrix_vals::Scalar, Eigen::Dynamic, 1> vals_copy = vals;
  igl::isolines_intrinsic(F, S.col(0), vals_copy, iB, iFI, iE, I);
  return std::make_tuple(npe::move(iB), npe::move(iFI), npe::move(iE), npe::move(I));

npe_end_code()
