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

#include <igl/faces_first.h>

const char *ds_faces_first = R"igl_Qu8mg5v7(

 FACES_FIRST Reorder vertices so that vertices in face list come before
   vertices that don't appear in the face list. This is especially useful if
   the face list contains only surface faces and you want surface vertices
   listed before internal vertices
   [RV,RF,IM] = faces_first(V,T);

Parameters
----------
    V  # vertices by 3 vertex positions
    F  # faces by 3 list of face indices

Returns
-------
    RV  # vertices by 3 vertex positions, order such that if the jth vertex is
      some face in F, and the kth vertex is not then j comes before k
    RF  # faces by 3 list of face indices, reindexed to use RV
    IM  #V by 1 list of indices such that: RF = IM(F) and RT = IM(T)
      and RV(IM,:) = V

See also
--------


Notes
-----
None

Examples
--------
    Tet mesh in (V,T,F)
    faces_first(V,F,IM);
    T = T.unaryExpr(bind1st(mem_fun( static_cast<VectorXi::Scalar&
       (VectorXi::*)(VectorXi::Index)>(&VectorXi::operator())),
       &IM)).eval();
)igl_Qu8mg5v7";

npe_function(faces_first)
npe_doc(ds_faces_first)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;

  EigenDenseLike<npe_Matrix_v> rv;
  EigenDenseLike<npe_Matrix_f> rf;
  Eigen::Matrix<typename npe_Matrix_f::Scalar, Eigen::Dynamic, 1> im;
  igl::faces_first(v_copy, f_copy, rv, rf, im);

  EigenDenseLike<npe_Matrix_f> im_res = im;
  return std::make_tuple(npe::move(rv), npe::move(rf), npe::move(im_res));
npe_end_code()
