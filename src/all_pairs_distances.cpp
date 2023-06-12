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
#include <igl/all_pairs_distances.h>

const char *ds_all_pairs_distances = R"igl_Qu8mg5v7(
compute distances between each point i in V and point j in U

Parameters
----------
V  #V by dim list of points
U  #U by dim list of points
squared  whether to return squared distances

Returns
-------
D  #V by #U matrix of distances, where D(i,j) gives the distance or squareed distance between V(i,:) and U(j,:)

See also
--------


Notes
-----


Examples
--------
D = all_pairs_distances(u,v)


)igl_Qu8mg5v7";

npe_function(all_pairs_distances)
npe_doc(ds_all_pairs_distances)

npe_arg(u, dense_float, dense_double)
npe_arg(v, npe_matches(u))
npe_arg(squared, bool)


npe_begin_code()
  assert_cols_match(u, v, "u", "v");
  assert_nonzero_rows(u, "u");
  assert_nonzero_rows(v, "v");
  //same input/output template
  EigenDenseLike<npe_Matrix_u> u_copy = u;
  EigenDenseLike<npe_Matrix_u> v_copy = v;

  EigenDenseLike<npe_Matrix_u> D;
  igl::all_pairs_distances(u_copy, v_copy, squared, D);
  return npe::move(D);

npe_end_code()


