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
#include <igl/orient_outward.h>

const char *ds_orient_outward = R"igl_Qu8mg5v7(

 Orient each component (identified by C) of a mesh (V,F) so the normals on
   average point away from the patch's centroid.

Parameters
----------
  V  #V by 3 list of vertex positions
  F  #F by 3 list of triangle indices
  C  #F list of components (output of orientable_patches)

Returns
-------
     FF  #F by 3 list of new triangle indices such that FF(~I,:) = F(~I,:) and
       FF(I,:) = fliplr(F(I,:)) (OK if &FF = &F)
     I  max(C)+1 list of whether face has been flipped

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(orient_outward)
npe_doc(ds_orient_outward)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(c, npe_matches(f))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, c, "f", "c");
  //problem with   if(&FF != &F)
  //problem with DerivedV as type
  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  Eigen::Matrix<typename npe_Matrix_c::Scalar, Eigen::Dynamic, 1> c_copy = c;

  EigenDenseLike<npe_Matrix_f> ff;
  Eigen::Matrix<typename npe_Matrix_f::Scalar, Eigen::Dynamic, 1> i_copy;
  igl::orient_outward(v_copy, f_copy, c_copy, ff, i_copy);
  EigenDenseLike<npe_Matrix_f> i = i_copy;
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()


