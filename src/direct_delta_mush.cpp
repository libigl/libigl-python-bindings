// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Kishore Venkateshan
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/direct_delta_mush.h>

const char* ds_direct_delta_mush = R"igl_Qu8mg5v7(
Perform Direct Delta Mush Skinning. 
Computes Direct Delta Mesh Skinning (Variant 0) from 
"Direct Delta Mush Skinning and Variants"

Parameters
----------
v  #V by 3 list of rest pose vertex positions
t  #E*4 by 3 list of bone pose transformations
omega #V by #E*10 list of precomputated matrix values

Returns
-------
u  #V by 3 list of output vertex positions

See also
--------


Notes
-----
None

Examples
--------
)igl_Qu8mg5v7";

npe_function(direct_delta_mush)
npe_doc(ds_direct_delta_mush)

npe_arg(v, dense_double)
npe_arg(t, dense_double)
npe_arg(omega, dense_double)

npe_begin_code()
  assert_cols_equals(v, 3, "v");
  assert_valid_bone_transforms(t, "t");
  assert_rows_equals(t, (omega.cols() * 4) / 10, "t");

  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> 
      t_affine(t.rows() / 4);
  
  for(int bone = 0; bone < t_affine.size(); ++bone)
  {
    t_affine[bone] = Eigen::Affine3d::Identity();
    t_affine[bone].matrix().block(0, 0, 3, 4) = t.block(bone * 4, 0, 4, 3).transpose();
  }

  EigenDenseLike<npe_Matrix_v> u;
  igl::direct_delta_mush(v, t_affine, omega, u);
  return npe::move(u);

npe_end_code()

const char* ds_direct_delta_mush_precomp = R"igl_Qu8mg5v7(
Do the Omega precomputation necessary for Direct Delta Mush Skinning.

Parameters
----------
v  #V by 3 list of rest pose vertex positions
f  #F by 3 list of triangle indices into rows of V
w  #V by #Edges list of weights
p  number of smoothing iterations
lambda  rotation smoothing step size
kappa   translation smoothness step size
alpha   translation smoothness blending weight

Returns
-------
omega : #V by #E*10 list of precomputated matrix values

See also
--------


Notes
-----
None

Examples
--------
)igl_Qu8mg5v7";

npe_function(direct_delta_mush_precomputation)
npe_doc(ds_direct_delta_mush_precomp)

npe_arg(v, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(w, npe_matches(v))
npe_arg(p, int)
npe_arg(lambda, double)
npe_arg(kappa, double)
npe_arg(alpha, double)

npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  Eigen::MatrixXd w_copy = w.template cast<double>();

  EigenDenseLike<npe_Matrix_v> omega;
  igl::direct_delta_mush_precomputation(v, f, w_copy, p, lambda, kappa, alpha, omega);
  return npe::move(omega);
  
npe_end_code()
