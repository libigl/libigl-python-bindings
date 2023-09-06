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
#include <igl/edges_to_path.h>

const char* ds_edges_to_path = R"igl_Qu8mg5v7(

EDGES_TO_PATH Given a set of undirected, unique edges such that all form a
  single connected compoent with exactly 0 or 2 nodes with valence =1,
  determine the/a path visiting all nodes.

Parameters
----------
E  #E by 2 list of undirected edges

Returns
-------
I  #E+1 list of nodes in order tracing the chain (loop), if the output
  is a loop then I(1) == I(end)
J  #I-1 list of indices into E of edges tracing I
K  #I-1 list of indices into columns of E {1,2} so that K(i) means that
  E(i,K(i)) comes before the other (i.e., E(i,3-K(i)) ). This means that
  I(i) == E(J(i),K(i)) for i<#I, or
  I == E(sub2ind(size(E),J([1:end end]),[K;3-K(end)]))))


See also
--------


Notes
-----
None

Examples
--------



)igl_Qu8mg5v7";

npe_function(edges_to_path)
npe_doc(ds_edges_to_path)

npe_arg(e, dense_int32, dense_int64)


npe_begin_code()
  assert_nonzero_rows(e, "e");
  assert_cols_equals(e, 2, "e");

  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::VectorXi i_copy;
  Eigen::VectorXi j_copy;
  Eigen::VectorXi k_copy;

  igl::edges_to_path(e_copy, i_copy, j_copy, k_copy);

  EigenDenseLike<npe_Matrix_e> i = i_copy.template cast<typename npe_Matrix_e::Scalar>();
  EigenDenseLike<npe_Matrix_e> j = i_copy.template cast<typename npe_Matrix_e::Scalar>();
  EigenDenseLike<npe_Matrix_e> k = i_copy.template cast<typename npe_Matrix_e::Scalar>();

  return std::make_tuple(npe::move(i), npe::move(j), npe::move(k));

npe_end_code()


