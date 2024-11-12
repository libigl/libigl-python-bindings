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






#include <igl/qslim.h>

const char* ds_qslim = R"igl_Qu8mg5v7(

Decimate (simplify) a triangle mesh in nD according to the paper
   "Simplifying Surfaces with Color and Texture using Quadric Error Metrics"
   by [Garland and Heckbert, 1987] (technically a followup to qslim). The
   mesh can have open boundaries but should be edge-manifold.

Parameters
----------
V  #V by dim list of vertex positions. Assumes that vertices w
F  #F by 3 list of triangle indices into V
max_m  desired number of output faces
block_intersections  whether to block intersections


Returns
-------
U  #U by dim list of output vertex posistions (can be same ref as V)
G  #G by 3 list of output face indices into U (can be same ref as G)
J  #G list of indices into F of birth face
I  #U list of indices into V of birth vertices


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(qslim)
npe_doc(ds_qslim)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(max_m, size_t)
npe_arg(block_intersections, bool)


npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd u;
  Eigen::MatrixXi g;
  Eigen::VectorXi j;
  Eigen::VectorXi i;
  bool success = igl::qslim(v_copy, f_copy, max_m, block_intersections, u, g, j, i);
  EigenDenseFloat u_row_major = u;
  EigenDenseInt g_row_major = g.template cast<typename EigenDenseInt::Scalar>();
  // FIXME: vector not allowing row major, but they should be essentially the same so i feel we can leave it as col major
  Eigen::Matrix<typename EigenDenseInt::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> j_row_major = j.template cast<typename EigenDenseInt::Scalar>();
  Eigen::Matrix<typename EigenDenseInt::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> i_row_major = i.template cast<typename EigenDenseInt::Scalar>();
  return std::make_tuple(success, npe::move(u_row_major), npe::move(g_row_major), npe::move(j_row_major), npe::move(i_row_major));

npe_end_code()


