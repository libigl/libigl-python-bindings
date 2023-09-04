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
#include <igl/tet_tet_adjacency.h>

const char *ds_tet_tet_adjacency = R"igl_Qu8mg5v7(
Constructs the tet_tet adjacency matrix for a given tet mesh with tets T

Parameters
----------
T  #T by 4 list of tets

Returns
-------
TT   #T by #4 adjacency matrix, the element i,j is the id of the tet adjacent to the j face of tet i
TTi  #T by #4 adjacency matrix, the element i,j is the id of face of the tet TT(i,j) that is adjacent to tet i

See also
--------

Notes
-----
the first face of a tet is [0,1,2], the second [0,1,3], the third [1,2,3], and the fourth [2,0,3].

Examples
--------

)igl_Qu8mg5v7";

npe_function(tet_tet_adjacency)
npe_doc(ds_tet_tet_adjacency)
npe_arg(t, dense_int32, dense_int64)
npe_begin_code()

  assert_nonzero_rows(t, "t");
  assert_cols_equals(t, 4, "t");
  EigenDenseLike<npe_Matrix_t> tt, tti;
  igl::tet_tet_adjacency(t, tt, tti);
  return std::make_tuple(npe::move(tt), npe::move(tti));

npe_end_code()
