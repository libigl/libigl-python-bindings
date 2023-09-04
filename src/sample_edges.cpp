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






#include <igl/sample_edges.h>

const char *ds_sample_edges = R"igl_Qu8mg5v7(
Compute samples_per_edge extra points along each edge in E defined over
   vertices of V.

Parameters
----------
V  vertices over which edges are defined, # vertices by dim
E  edge list, # edges by 2
k  number of extra samples to be computed along edge not including start and end points

Returns
-------
S  sampled vertices, size less than # edges * (2+k) by dim always begins
          with V so that E is also defined over S

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(sample_edges)
npe_doc(ds_sample_edges)

npe_arg(v, dense_float, dense_double)
npe_arg(e, dense_int32, dense_int64)
npe_arg(k, int)


npe_begin_code()
  assert_nonzero_rows(v, "v");
  assert_nonzero_rows(e, "e");
  assert_cols_equals(e, 2, "e");

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::MatrixXd s_copy;
  igl::sample_edges(v_copy, e_copy, k, s_copy);
  EigenDenseLike<npe_Matrix_v> s = s_copy.template cast<npe_Scalar_v>();
  return npe::move(s);

npe_end_code()


