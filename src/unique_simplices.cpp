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
#include <igl/unique_simplices.h>

const char *ds_unique_simplices = R"igl_Qu8mg5v7(
Find *combinatorially* unique simplices in F.  **Order independent**
Parameters
----------
F  #F by simplex-size list of simplices

Returns
-------
    FF  #FF by simplex-size list of unique simplices in F
    IA  #FF index vector so that FF == sort(F(IA,:),2);
    IC  #F index vector so that sort(F,2) == FF(IC,:);

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unique_simplices)
npe_doc(ds_unique_simplices)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f);

  EigenDenseLike<npe_Matrix_f> ff;
  Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> ia;
  Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> ic;
  igl::unique_simplices(f, ff, ia, ic);
  return std::make_tuple(npe::move(ff), npe::move(ia), npe::move(ic));

npe_end_code()


