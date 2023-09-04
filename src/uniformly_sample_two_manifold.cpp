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






#include <igl/uniformly_sample_two_manifold.h>

const char* ds_uniformly_sample_two_manifold_internal = R"igl_Qu8mg5v7(

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by
   furthest point relaxation as described in "Fast Automatic Skinning
   Transformations"

   [Jacobson et al. 12] Section 3.3.

Parameters
----------
W  #W by dim positions of mesh in weight space
F  #F by 3 indices of triangles
k  number of samplse
push  factor by which corners should be pushed away


Returns
-------
WS  k by dim locations in weights space


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold_internal)
npe_doc(ds_uniformly_sample_two_manifold_internal)

npe_arg(w, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  assert_valid_23d_tri_mesh(w, f);
  // TODO: remove __copy
  Eigen::MatrixXd w_copy = w.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd ws;
  igl::uniformly_sample_two_manifold(w_copy, f_copy, k, push, ws);
  EigenDenseFloat ws_row_major = ws;
  return npe::move(ws_row_major);

npe_end_code()





const char* ds_uniformly_sample_two_manifold_at_vertices = R"igl_Qu8mg5v7(

Find uniform sampling up to placing samples on mesh vertices

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold_at_vertices)
npe_doc(ds_uniformly_sample_two_manifold_at_vertices)

npe_arg(ow, dense_float, dense_double)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  // TODO: remove __copy
  Eigen::MatrixXd ow_copy = ow.template cast<double>();
  // FIXME: vector not allowing row major, but they should be essentially the same so i feel we can leave it as col major
  Eigen::VectorXi s;
  igl::uniformly_sample_two_manifold_at_vertices(ow_copy, k, push, s);
  Eigen::Matrix<typename EigenDenseInt::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> s_out = s.template cast<typename EigenDenseInt::Scalar>();
  return npe::move(s_out);

npe_end_code()


