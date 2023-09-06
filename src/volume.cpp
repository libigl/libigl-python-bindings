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
#include <igl/volume.h>

const char *ds_volume = R"igl_Qu8mg5v7(
Computes volume for all tets of a given tet mesh (V,T)

Parameters
----------
V  #V by dim list of vertex positions
T  #V by 4 list of tet indices

Returns
-------
vol  #T list of dihedral angles (in radians)

See also
--------


Notes
-----
None

Examples
--------
   vol = volume(V,T)

)igl_Qu8mg5v7";

npe_function(volume)
npe_doc(ds_volume)

npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tet_mesh(v, t);

EigenDenseLike<npe_Matrix_v> vol;
igl::volume(v, t, vol);
return npe::move(vol);
npe_end_code()




const char* ds_volume1 = R"igl_Qu8mg5v71(
Compute volumes of a list of tets defined by a, b, c, d

Parameters
----------
a,b,c,d list of vertices vertices of the tets

Returns
-------
vol  volume of the tets

See also
--------


Notes
-----
None

Examples
--------
)igl_Qu8mg5v71";

npe_function(volume_from_vertices)
npe_doc(ds_volume1)

npe_arg(a, dense_float, dense_double)
npe_arg(b, npe_matches(a))
npe_arg(c, npe_matches(a))
npe_arg(d, npe_matches(a))


npe_begin_code()
  assert_cols_equals(a, 3, "a");
  // assert_cols_equals(b, 3, "b");
  // assert_cols_equals(c, 3, "c");
  // assert_cols_equals(d, 3, "d");

  assert_nonzero_rows(a, "a");
  // assert_nonzero_rows(b, "b");
  // assert_nonzero_rows(c, "c");
  // assert_nonzero_rows(d, "d");

  assert_shapes_match(a, b, "a", "b");
  assert_shapes_match(a, c, "a", "c");
  assert_shapes_match(a, d, "a", "d");

  EigenDenseLike<npe_Matrix_a> vol;
  igl::volume(a, b, c, d, vol);
  return npe::move(vol);
npe_end_code()



const char *ds_volume2 = R"igl_Qu8mg5v72(
Computes volume for all tets from edge lengths
Parameters
----------
L  #V by 6 list of edge lengths (see edge_lengths)

Returns
-------
vol  volume of the tets

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v72";

npe_function(volume_from_edges)
npe_doc(ds_volume2)

npe_arg(l, dense_float, dense_double)

npe_begin_code()
  assert_cols_equals(l, 6, "l");
  assert_nonzero_rows(l, "l");

  EigenDenseLike<npe_Matrix_l> vol;
  igl::volume(l, vol);
  return npe::move(vol);
npe_end_code()


const char* ds_volume_single = R"igl_Qu8mg5v73(
Volume of a single tet
Parameters
----------
a,b,c,d vertices

Returns
-------
volume

See also
--------


Notes
-----
None

Examples
--------

 Single tet
)igl_Qu8mg5v73";

npe_function(volume_single)
npe_doc(ds_volume_single)

npe_arg(a, dense_float, dense_double)
npe_arg(b, npe_matches(a))
npe_arg(c, npe_matches(a))
npe_arg(d, npe_matches(a))


npe_begin_code()
  assert_size_equals(a, 3, "a");
  assert_size_equals(b, 3, "b");
  assert_size_equals(c, 3, "c");
  assert_size_equals(d, 3, "d");
  const bool must_transpose = a.rows() == 3;

  const Eigen::Matrix<npe_Scalar_a, 1, 3> a_copy = must_transpose ? a.transpose().eval() : a;
  const Eigen::Matrix<npe_Scalar_a, 1, 3> b_copy = must_transpose ? b.transpose().eval() : b;
  const Eigen::Matrix<npe_Scalar_a, 1, 3> c_copy = must_transpose ? c.transpose().eval() : c;
  const Eigen::Matrix<npe_Scalar_a, 1, 3> d_copy = must_transpose ? d.transpose().eval() : d;

  double vol = igl::volume_single(a_copy, b_copy, c_copy, d_copy);
  return vol;
npe_end_code()


