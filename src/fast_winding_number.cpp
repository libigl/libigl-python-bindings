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
#include <igl/fast_winding_number.h>

const char *ds_fast_winding_number_for_points = R"igl_Qu8mg5v7xxx1(
Evaluate the fast winding number for point data, with default expansion
order and beta (both are set to 2).

This function performes the precomputation and evaluation all in one.
If you need to acess the precomuptation for repeated evaluations, use the
two functions designed for exposed precomputation (described above).

Parameters
----------
P  #P by 3 list of point locations
N  #P by 3 list of point normals
A  #P by 1 list of point areas
Q  #Q by 3 list of query points for the winding number

Returns
-------
WN  #Q by 1 list of windinng number values at each query point

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7xxx1";

npe_function(fast_winding_number_for_points)
npe_doc(ds_fast_winding_number_for_points)
npe_arg(p, dense_float, dense_double)
npe_arg(n, npe_matches(p))
npe_arg(a, npe_matches(p))

npe_arg(q, npe_matches(p))

npe_begin_code()
  assert_nonzero_rows(p, "p");
  assert_cols_equals(p, 3, "p");

  assert_cols_equals(n, 3, "p");
  assert_rows_match(p, n, "p", "n");

  assert_size_equals(a, p.rows(), "a");

  assert_cols_equals(q, 3, "q");
  assert_nonzero_rows(q, "q");

  EigenDenseLike<npe_Matrix_p> a_copy = a;

  EigenDenseLike<npe_Matrix_p> wn;
  igl::fast_winding_number(p, n, a_copy, q, wn);
  return npe::move(wn);

npe_end_code()




const char *ds_fast_winding_number_for_meshes = R"igl_Qu8mg5v7xxx2(
Compute approximate winding number of a triangle soup mesh according to
"Fast Winding Numbers for Soups and Clouds" [Barill et al. 2018].

Parameters
----------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of triangle mesh indices into rows of V
Q  #Q by 3 list of query points for the winding number

Returns
-------
WN  #Q by 1 list of windinng number values at each query point

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7xxx2";

npe_function(fast_winding_number_for_meshes)
npe_doc(ds_fast_winding_number_for_meshes)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)

npe_arg(q, npe_matches(v))

npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_cols_equals(q, 3, "q");
  assert_nonzero_rows(q, "q");

  EigenDenseLike<npe_Matrix_v> wn;
  igl::fast_winding_number(v, f, q, wn);
  return npe::move(wn);

npe_end_code()