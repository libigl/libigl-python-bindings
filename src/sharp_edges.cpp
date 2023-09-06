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
#include <pybind11/stl.h>

#include <igl/sharp_edges.h>

const char *ds_sharp_edges = R"igl_Qu8mg5v7xxxx(
SHARP_EDGES Given a mesh, compute sharp edges.

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of triangle mesh indices into V
angle  dihedral angle considered to sharp (e.g., igl::PI * 0.11)

Returns
-------
SE  #SE by 2 list of edge indices into V
E   #e by 2 list of edges in no particular order
uE  #uE by 2 list of unique undirected edges
EMAP #F*3 list of indices into uE, mapping each directed edge to unique
undirected edge so that uE(EMAP(f+#F*c)) is the unique edge
corresponding to E.row(f+#F*c)
uE2E  #uE list of lists of indices into E of coexisting edges, so that
E.row(uE2E[i][j]) corresponds to uE.row(i) for all j in
0..uE2E[i].size()-1.
sharp  #SE list of indices into uE revealing sharp undirected edges

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7xxxx";

npe_function(sharp_edges)
npe_doc(ds_sharp_edges)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(angle, double)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  // Eigen::MatrixXd v_copy = v.template cast<double>();
  // Eigen::MatrixXi e_copy = e.template cast<int>();
  // Eigen::MatrixXd s_copy;

  EigenDense<npe_Scalar_f> se;
  EigenDense<npe_Scalar_f> e;
  EigenDense<npe_Scalar_f> ue;
  Eigen::Matrix<npe_Scalar_f,Eigen::Dynamic,1> emap;
  std::vector<std::vector<typename EigenDenseInt::Scalar>> u_e2_e;
  std::vector<typename EigenDenseInt::Scalar> sharp;
  igl::sharp_edges(v, f, angle, se, e, ue, emap, u_e2_e, sharp);
  return std::make_tuple(npe::move(se), npe::move(e), npe::move(ue), npe::move(emap), u_e2_e, sharp);

  npe_end_code()
