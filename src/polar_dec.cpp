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
#include <igl/polar_dec.h>

const char *ds_polar_dec = R"igl_Qu8mg5v7(

Computes the polar decomposition (R,T) of a matrix A


Parameters
----------
A  3 by 3 matrix to be decomposed

Returns
-------

R  3 by 3 orthonormal matrix part of decomposition
T  3 by 3 stretch matrix part of decomposition

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(polar_dec)
npe_doc(ds_polar_dec)

npe_arg(a, dense_float, dense_double)

npe_begin_code()
  assert_rows_equals(a, 3, "a");
  assert_cols_equals(a, 3, "a");

  EigenDense<npe_Scalar_a> a_copy = a;
  EigenDense<npe_Scalar_a> r;
  EigenDense<npe_Scalar_a> t;
  igl::polar_dec(a_copy, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


