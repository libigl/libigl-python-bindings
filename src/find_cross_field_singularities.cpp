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
#include <igl/find_cross_field_singularities.h>

const char *ds_find_cross_field_singularities = R"igl_Qu8mg5v7(
Computes singularities of a cross field, assumed combed

Parameters
----------
V                #V by 3 eigen Matrix of mesh vertex 3D positions
F                #F by 3 eigen Matrix of face indices
Handle_MMatch    #F by 3 eigen Matrix containing the integer missmatch of the cross field
                across all face edges

Returns
-------
isSingularity    #V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex
singularityIndex #V by 1 integer eigen Vector containing the singularity indices

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(find_cross_field_singularities)
npe_doc(ds_find_cross_field_singularities)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(handle_m_match, npe_matches(f))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, handle_m_match, "F", "Handle_MMatch");
  assert_cols_equals(handle_m_match, 3, "Handle_MMatch");

  EigenDenseLike<npe_Matrix_f> is_singularity;
  EigenDenseLike<npe_Matrix_f> singularity_index;
  igl::find_cross_field_singularities(v, f, handle_m_match, is_singularity, singularity_index);
  return std::make_tuple(npe::move(is_singularity), npe::move(singularity_index));

npe_end_code()



const char *ds_find_cross_field_singularities_from_field = R"igl_Qu8mg5v7(

Wrapper that calculates the missmatch if it is not provided.
Note that the field in PD1 and PD2 MUST BE combed (see igl::comb_cross_field).

Parameters
----------

V                #V by 3 eigen Matrix of mesh vertex 3D positions
F                #F by 3 eigen Matrix of face (quad) indices
PD1              #F by 3 eigen Matrix of the first per face cross field vector
PD2              #F by 3 eigen Matrix of the second per face  cross field vector

Returns
-------
isSingularity    #V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex
singularityIndex #V by 1 integer eigen Vector containing the singularity indices

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(find_cross_field_singularities_from_field)
npe_doc(ds_find_cross_field_singularities_from_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))
npe_default_arg(is_combed, bool, false)


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

  EigenDenseLike<npe_Matrix_f> is_singularity;
  EigenDenseLike<npe_Matrix_f> singularity_index;
  igl::find_cross_field_singularities(v_copy, f_copy, pd1_copy, pd2_copy, is_singularity, singularity_index, is_combed);
  return std::make_tuple(npe::move(is_singularity), npe::move(singularity_index));

npe_end_code()


