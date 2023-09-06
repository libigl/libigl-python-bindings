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
#include <igl/comb_frame_field.h>

const char* ds_comb_frame_field = R"igl_Qu8mg5v7(

Parameters
----------
V            #V by 3 eigen Matrix of mesh vertex 3D positions
F            #F by 3 eigen Matrix of face indices
PD1          #F by 3 eigen Matrix of the first per face cross field vector
PD2          #F by 3 eigen Matrix of the second per face cross field vector
BIS1_combed  #F by 3 eigen Matrix of the first combed bisector field vector
BIS2_combed  #F by 3 eigen Matrix of the second combed bisector field vector

Returns
-------
PD1_combed  #F by 3 eigen Matrix of the first combed cross field vector
PD2_combed  #F by 3 eigen Matrix of the second combed cross field vector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(comb_frame_field)
npe_doc(ds_comb_frame_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(pd1))
npe_arg(bis1_combed, npe_matches(pd1))
npe_arg(bis2_combed, npe_matches(pd1))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, pd1, "F", "PD1");
  assert_rows_match(f, pd2, "F", "PD2");

  assert_rows_match(f, bis1_combed, "F", "BIS1_combed");
  assert_rows_match(f, bis2_combed, "F", "BIS2_combed");

  assert_cols_equals(pd1, 3, "PD1");
  assert_cols_equals(pd2, 3, "PD2");

  assert_cols_equals(bis1_combed, 3, "BIS1_combed");
  assert_cols_equals(bis2_combed, 3, "BIS2_combed");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> pd1_copy = pd1;
  EigenDenseLike<npe_Matrix_v> pd2_copy = pd2;
  EigenDenseLike<npe_Matrix_v> bis1_combed_copy = bis1_combed;
  EigenDenseLike<npe_Matrix_v> bis2_combed_copy = bis2_combed;

  EigenDenseLike<npe_Matrix_v> pd1_combed;
  EigenDenseLike<npe_Matrix_v> pd2_combed;

  igl::comb_frame_field(v_copy, f_copy, pd1_copy, pd2_copy, bis1_combed_copy, bis2_combed_copy, pd1_combed, pd2_combed);
  return std::make_tuple(npe::move(pd1_combed), npe::move(pd2_combed));

npe_end_code()


