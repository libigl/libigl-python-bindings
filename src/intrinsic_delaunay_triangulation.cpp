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
#include <igl/intrinsic_delaunay_triangulation.h>

const char *ds_intrinsic_delaunay_triangulation = R"igl_Qu8mg5v7(

INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
"intrinsic Delaunay". See "An algorithm for the construction of intrinsic
delaunay triangulations with applications to digital geometry processing"
[Fisher et al. 2007].

Parameters
----------

l_in  #F_in by 3 list of edge lengths (see edge_lengths)
F_in  #F_in by 3 list of face indices into some unspecified vertex list V

Returns
-------

l  #F by 3 list of edge lengths
F  #F by 3 list of new face indices. Note: Combinatorially F may contain
  non-manifold edges, duplicate faces and self-loops (e.g., an edge [1,1]
  or a face [1,1,1]). However, the *intrinsic geometry* is still
  well-defined and correct. See [Fisher et al. 2007] Figure 3 and 2nd to
  last paragraph of 1st page. Since F may be "non-eddge-manifold" in the
  usual combinatorial sense, it may be useful to call the more verbose
  overload below if disentangling edges will be necessary later on.
  Calling unique_edge_map on this F will give a _different_ result than
  those outputs.

See also
--------

is_intrinsic_delaunay

Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_triangulation)
npe_doc(ds_intrinsic_delaunay_triangulation)

npe_arg(l_in, dense_float, dense_double)
npe_arg(f_in, dense_int32, dense_int64)


npe_begin_code()
  assert_rows_match(l_in, f_in, "l_in", "f_in");
  assert_cols_equals(l_in, 3, "l_in");
  assert_valid_tri_mesh_faces(f_in);

  EigenDense<npe_Scalar_l_in> l;
  EigenDense<npe_Scalar_f_in> f;
  igl::intrinsic_delaunay_triangulation(l_in, f_in, l, f);
  return std::make_tuple(npe::move(l), npe::move(f));

npe_end_code()


const char *ds_intrinsic_delaunay_triangulation1 = R"igl_Qu8mg5v71(

INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
"intrinsic Delaunay". See "An algorithm for the construction of intrinsic
delaunay triangulations with applications to digital geometry processing"
[Fisher et al. 2007].

Parameters
----------

l_in  #F_in by 3 list of edge lengths (see edge_lengths)
F_in  #F_in by 3 list of face indices into some unspecified vertex list V

Returns
-------

E  #F*3 by 2 list of all directed edges, such that E.row(f+#F*c) is the
       edge opposite F(f,c)
uE  #uE by 2 list of unique undirected edges
EMAP #F*3 list of indices into uE, mapping each directed edge to unique
  undirected edge
uE2E  #uE list of lists of indices into E of coexisting edges

See also
--------
unique_edge_map

Notes
-----
None

Examples
--------

)igl_Qu8mg5v71";

npe_function(intrinsic_delaunay_triangulation_edges)
npe_doc(ds_intrinsic_delaunay_triangulation1)

npe_arg(l_in, dense_float, dense_double)
npe_arg(f_in, dense_int32, dense_int64)


npe_begin_code()
  assert_rows_match(l_in, f_in, "l_in", "f_in");
  assert_cols_equals(l_in, 3, "l_in");
  assert_valid_tri_mesh_faces(f_in);

  EigenDense<npe_Scalar_l_in> l;
  EigenDense<npe_Scalar_f_in> f;
  EigenDense<npe_Scalar_f_in> e;
  EigenDense<npe_Scalar_f_in> u_e;
  Eigen::Matrix<npe_Scalar_f_in,Eigen::Dynamic,1> emap;
  std::vector<std::vector<npe_Scalar_f_in>> u_e2_e;
  igl::intrinsic_delaunay_triangulation(l_in, f_in, l, f, e, u_e, emap, u_e2_e);
  std::vector<std::vector<typename EigenDenseInt::Scalar>> u_e2_e_copy;

  u_e2_e_copy.resize(u_e2_e.size());

  for(size_t i = 0; i < u_e2_e_copy.size(); ++i)
  {
    u_e2_e_copy.resize(u_e2_e[i].size());
    for (size_t j = 0; j < u_e2_e_copy[i].size(); ++j)
      u_e2_e_copy[i][j] = u_e2_e[i][j];
  }

  return std::make_tuple(npe::move(l), npe::move(f), npe::move(e), npe::move(u_e), npe::move(emap), u_e2_e_copy);

  npe_end_code()
