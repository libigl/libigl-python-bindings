// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/resolve_duplicated_faces.h>

const char* ds_resolve_duplicated_faces = R"igl_Qu8mg5v7(

Resolve duplicated faces according to the following rules per unique face:
   - If the number of positively oriented faces equals the number of
      negatively oriented faces, remove all duplicated faces at this triangle.
   - If the number of positively oriented faces equals the number of
      negatively oriented faces plus 1, keeps one of the positively oriented
      face.
   - If the number of positively oriented faces equals the number of
      negatively oriented faces minus 1, keeps one of the negatively oriented
      face.
   - If the number of postively oriented faces differ with the number of
      negativley oriented faces by more than 1, the mesh is not orientable.
      An exception will be thrown.

Parameters
----------
F1  #F1 by 3 array of input faces.

Returns
-------
F2  #F2 by 3 array of output faces without duplicated faces.
J   #F2 list of indices into F1.

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(resolve_duplicated_faces)
npe_doc(ds_resolve_duplicated_faces)

npe_arg(f1, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f1, "f1");
  // TODO: remove __copy
  // same problem that DerivedF1 causes problem, can be prevented
  Eigen::MatrixXi f1_copy = f1.template cast<int>();
  Eigen::MatrixXi f2_copy;
  Eigen::Matrix<npe_Scalar_f1,Eigen::Dynamic,1> j;
  igl::resolve_duplicated_faces(f1_copy, f2_copy, j);
  EigenDenseLike<npe_Matrix_f1> f2 = f2_copy.template cast<npe_Scalar_f1>();
  return std::make_tuple(npe::move(f2), npe::move(j));

npe_end_code()


