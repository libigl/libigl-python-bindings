// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __miss

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/procrustes.h>




const char* ds_procrustes = R"igl_Qu8mg5v7(

Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d
   find best scale s, orthogonal R  and translation t s.t. |s*X*R + t - Y|^2
   is minimized.

Parameters
----------
X  #V by DIM first list of points
Y  #V by DIM second list of points
includeScaling  if scaling should be allowed
includeReflections  if R is allowed to be a reflection


Returns
-------
scale  scaling
R      orthogonal matrix
t      translation


See also
--------


Notes
-----
None

Examples
--------
MatrixXd X, Y; (containing 3d points as rows)
double scale;
MatrixXd R;
VectorXd t;
igl::procrustes(X,Y,true,false,scale,R,t);
R *= scale;
MatrixXd Xprime = (X * R).rowwise() + t.transpose();
  
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_float, dense_double)
npe_arg(y, npe_matches(x))
npe_arg(include_scaling, bool)
npe_arg(include_reflections, bool)

npe_begin_code()

  assert_cols_match(x, y, "x", "y");
  assert_nonzero_rows(x, "x");
  double scale;
  EigenDenseLike<npe_Matrix_x> r, t;
  igl::procrustes(x, y, include_scaling, include_reflections, scale, r, t);
  return std::make_tuple(scale, npe::move(r), npe::move(t));

npe_end_code()

