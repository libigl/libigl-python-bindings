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



#include <igl/directed_edge_orientations.h>

const char *ds_directed_edge_orientations = R"igl_Qu8mg5v7(
 Determine rotations that take each edge from the x-axis to its given rest
   orientation.
Parameters
----------
C  #C by 3 list of edge vertex positions
E  #E by 2 list of directed edges

Returns
-------
Q  #E list of quaternions

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(directed_edge_orientations)
npe_doc(ds_directed_edge_orientations)

npe_arg(c, dense_float, dense_double)
npe_arg(e, dense_int32, dense_int64)


npe_begin_code()
  assert_cols_equals(c, 3, "C");
  assert_cols_equals(e, 2, "E");
  Eigen::MatrixXd c_copy = c.template cast<double>();
  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > q;
  igl::directed_edge_orientations(c_copy, e, q);
  EigenDenseLike<npe_Matrix_c> q_copy(q.size(), 4);
  for(size_t i = 0; i < q.size(); ++i){
    q_copy(i, 0) = q[i].x();
    q_copy(i, 1) = q[i].y();
    q_copy(i, 2) = q[i].z();
    q_copy(i, 3) = q[i].w();
  }
  return npe::move(q_copy);

  npe_end_code()
