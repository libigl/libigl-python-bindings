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
#include <igl/compute_frame_field_bisectors.h>

const char* ds_compute_frame_field_bisectors = R"igl_Qu8mg5v7(

Compute bisectors of a frame field defined on mesh faces

Parameters
----------
V     #V by 3 eigen Matrix of mesh vertex 3D positions
F     #F by 3 eigen Matrix of face (triangle) indices
B1    #F by 3 eigen Matrix of face (triangle) base vector 1
B2    #F by 3 eigen Matrix of face (triangle) base vector 2
PD1   #F by 3 eigen Matrix of the first per face frame field vector
PD2   #F by 3 eigen Matrix of the second per face frame field vector

Returns
-------
BIS1  #F by 3 eigen Matrix of the first per face frame field bisector
BIS2  #F by 3 eigen Matrix of the second per face frame field bisector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(compute_frame_field_bisectors)
npe_doc(ds_compute_frame_field_bisectors)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(b1, npe_matches(v))
npe_arg(b2, npe_matches(v))
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, b1, "F", "B1");
  assert_rows_match(f, b2, "F", "B2");
  assert_cols_equals(b1, 3, "b1");
  assert_cols_equals(b2, 3, "b2");

  assert_rows_match(f, pd1, "F", "PD1");
  assert_rows_match(f, pd2, "F", "PD2");
  assert_cols_equals(pd1, 3, "PD1");
  assert_cols_equals(pd2, 3, "PD2");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> b1_copy = b1;
  EigenDenseLike<npe_Matrix_v> b2_copy = b2;
  EigenDenseLike<npe_Matrix_v> pd1_copy = pd1;
  EigenDenseLike<npe_Matrix_v> pd2_copy = pd2;

  EigenDenseLike<npe_Matrix_v> bis1;
  EigenDenseLike<npe_Matrix_v> bis2;
  igl::compute_frame_field_bisectors(v_copy, f_copy, b1_copy, b2_copy, pd1_copy, pd2_copy, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()



const char* ds_compute_frame_field_bisectors_no_basis = R"igl_Qu8mg5v7(

Wrapper without given basis vectors.

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

npe_function(compute_frame_field_bisectors_no_basis)
npe_doc(ds_compute_frame_field_bisectors_no_basis)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  assert_rows_match(f, pd1, "F", "PD1");
  assert_rows_match(f, pd2, "F", "PD2");
  assert_cols_equals(pd1, 3, "PD1");
  assert_cols_equals(pd2, 3, "PD2");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> pd1_copy = pd1;
  EigenDenseLike<npe_Matrix_v> pd2_copy = pd2;

  EigenDenseLike<npe_Matrix_v> bis1;
  EigenDenseLike<npe_Matrix_v> bis2;

  igl::compute_frame_field_bisectors(v_copy, f_copy, pd1_copy, pd2_copy, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()


