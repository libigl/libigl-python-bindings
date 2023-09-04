// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/remove_unreferenced.h>

const char* ds_remove_unreferenced = R"igl_Qu8mg5v7(

Remove unreferenced vertices from V, updating F accordingly

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by ss list of simplices (Values of -1 are quitely skipped)


Returns
-------
NV  #NV by dim list of mesh vertex positions
NF  #NF by ss list of simplices
IM  #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)
  and V(find(IM<=size(NV,1)),:) = NV
J  #RV by 1 list, such that RV = V(J,:)


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(remove_unreferenced)
npe_doc(ds_remove_unreferenced)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenDenseLike<npe_Matrix_v> nv;
  EigenDenseLike<npe_Matrix_f> nf;
  Eigen::Matrix<npe_Scalar_f,Eigen::Dynamic,1> i, j;
  igl::remove_unreferenced(v, f, nv, nf, i, j);
  return std::make_tuple(npe::move(nv), npe::move(nf), npe::move(i), npe::move(j));

npe_end_code()

