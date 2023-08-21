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






#include <igl/point_mesh_squared_distance.h>

const char *ds_point_mesh_squared_distance = R"igl_Qu8mg5v7(
 Compute distances from a set of points P to a triangle mesh (V,F)

Parameters
----------
P  #P by 3 list of query point positions
V  #V by 3 list of vertex positions
Ele  #Ele by (3|2|1) list of (triangle|edge|point) indices

Returns
-------
sqrD  #P list of smallest squared distances
I  #P list of primitive indices corresponding to smallest distances
C  #P by 3 list of closest points

See also
--------


Notes
-----
Known bugs: This only computes distances to given primitivess. So
unreferenced vertices are ignored. However, degenerate primitives are
handled correctly: triangle [1 2 2] is treated as a segment [1 2], and
triangle [1 1 1] is treated as a point. So one _could_ add extra
combinatorially degenerate rows to Ele for all unreferenced vertices to
also get distances to points.

Examples
--------

)igl_Qu8mg5v7";

npe_function(point_mesh_squared_distance)
npe_doc(ds_point_mesh_squared_distance)

npe_arg(p, dense_float, dense_double)
npe_arg(v, dense_float, dense_double)
npe_arg(ele, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_nonzero_rows(p, "P");
  assert_nonzero_rows(v, "V");
  assert_nonzero_rows(ele, "Ele");

  Eigen::MatrixXd p_copy;
  if(p.size() == 2 || p.size() == 3)
  {
    p_copy.resize(1, p.size());
    for(int i = 0; i < p.size(); ++i)
      p_copy(0, i) = p(i, 0);
  }
  else
    p_copy = p.template cast<double>();
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi ele_copy = ele.template cast<int>();

  Eigen::MatrixXd sqr_d;
  Eigen::MatrixXi i;
  Eigen::MatrixXd c;

  igl::point_mesh_squared_distance(p_copy, v_copy, ele_copy, sqr_d, i, c);
  EigenDenseLike<npe_Matrix_p> sqr_d_row_maj = sqr_d.template cast<typename npe_Matrix_p::Scalar>();
  EigenDenseLike<npe_Matrix_ele> i_row_maj = i.template cast<typename npe_Matrix_ele::Scalar>();
  EigenDenseLike<npe_Matrix_p> c_row_maj = c.template cast<typename npe_Matrix_p::Scalar>();
return std::make_tuple(npe::move(sqr_d_row_maj), npe::move(i_row_maj), npe::move(c_row_maj));

npe_end_code()


