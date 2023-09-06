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





#include <igl/collapse_small_triangles.h>

const char* ds_collapse_small_triangles = R"igl_Qu8mg5v7(

Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the
  original faces and vertices of (V,F) except any small triangles have been
  removed via collapse.

  We are *not* following the rules in "Mesh Optimization" [Hoppe et al]
  Section 4.2. But for our purposes we don't care about this criteria.

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of triangle indices into V
eps  epsilon for smallest allowed area treated as fraction of squared bounding box
  diagonal

Returns
-------
FF  #FF by 3 list of triangle indices into V


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(collapse_small_triangles)
npe_doc(ds_collapse_small_triangles)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(eps, double)


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXi ff;
  igl::collapse_small_triangles(v_copy, f_copy, eps, ff);
  EigenDenseInt ff_row_major = ff.template cast<typename EigenDenseInt::Scalar>();;
  return npe::move(ff_row_major);

npe_end_code()


