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
#include <pybind11/stl.h>
#include <igl/unique_edge_map.h>

const char *ds_unique_edge_map = R"igl_Qu8mg5v7xxx(
Construct relationships between facet "half"-(or rather "viewed")-edges E
to unique edges of the mesh seen as a graph.

Parameters
----------
F  #F by 3  list of simplices


Returns
-------
E  #F*3 by 2 list of all directed edges, such that E.row(f+#F*c) is the
edge opposite F(f,c)
uE  #uE by 2 list of unique undirected edges
EMAP #F*3 list of indices into uE, mapping each directed edge to unique
undirected edge so that uE(EMAP(f+#F*c)) is the unique edge
corresponding to E.row(f+#F*c)
uE2E  #uE list of lists of indices into E of coexisting edges, so that
E.row(uE2E[i][j]) corresponds to uE.row(i) for all j in
0..uE2E[i].size()-1.


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7xxx";

npe_function(unique_edge_map)
npe_doc(ds_unique_edge_map)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tri_mesh_faces(f);

  EigenDenseLike<npe_Matrix_f> E;
  EigenDenseLike<npe_Matrix_f> uE;
  Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> EMAP;
  std::vector<std::vector<typename EigenDenseInt::Scalar>> uE2E;
  igl::unique_edge_map(f, E, uE, EMAP, uE2E);
  return std::make_tuple(npe::move(E), npe::move(uE), npe::move(EMAP), uE2E);

  npe_end_code()
