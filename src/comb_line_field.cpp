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
#include <igl/comb_line_field.h>

const char *ds_comb_line_field = R"igl_Qu8mg5v7(

Parameters
----------
V          #V by 3 eigen Matrix of mesh vertex 3D positions
F          #F by 3 eigen Matrix of face indices
PD1in      #F by 3 eigen Matrix of the first per face cross field vector

Returns
-------
PD1out      #F by 3 eigen Matrix of the first combed cross field vector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(comb_line_field)
npe_doc(ds_comb_line_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(pd1in, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, pd1in, "F", "PD1in");
  assert_cols_equals(pd1in, 3, "PD1in");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> pd1in_copy = pd1in;

  EigenDenseLike<npe_Matrix_v> pd1out;
  igl::comb_line_field(v_copy, f_copy, pd1in_copy, pd1out);
  return npe::move(pd1out);

npe_end_code()


