// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>






#include <igl/partition.h>

const char *ds_partition = R"igl_Qu8mg5v7(

PARTITION partition vertices into groups based on each
vertex's vector: vertices with similar coordinates (close in
space) will be put in the same group.

Parameters
----------
W  #W by dim coordinate matrix
k  desired number of groups default is dim

Returns
-------
G  #W list of group indices (1 to k) for each vertex, such that vertex i is assigned to group G(i)
S  k  list of seed vertices
D  #W list of squared distances for each vertex to it's corresponding closest seed

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(partition)
npe_doc(ds_partition)

npe_arg(w, dense_float, dense_double)
npe_arg(k, int)


npe_begin_code()
  assert_nonzero_rows(w, "w");

  Eigen::MatrixXd w_copy = w.template cast<double>();
  Eigen::Matrix<int, Eigen::Dynamic, 1> g_copy;
  Eigen::Matrix<int, Eigen::Dynamic, 1> s_copy;
  Eigen::Matrix<double, Eigen::Dynamic, 1> d_copy;
  igl::partition(w_copy, k, g_copy, s_copy, d_copy);

  EigenDenseInt g = g_copy.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseInt s = s_copy.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseLike<npe_Matrix_w> d = d_copy.template cast<npe_Scalar_w>();

  return std::make_tuple(npe::move(g), npe::move(s), npe::move(d));

npe_end_code()


