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




#include <igl/edge_collapse_is_valid.h>

const char *ds_edge_collapse_is_valid = R"igl_Qu8mg5v7(

 Assumes (V,F) is a closed manifold mesh (except for previouslly collapsed faces which should be set to:
   [IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL].
   Tests whether collapsing exactly two faces and exactly 3 edges from E (e
   and one side of each face gets collapsed to the other) will result in a
   mesh with the same topology.

Parameters
----------
  e  index into E of edge to try to collapse. E(e,:) = [s d] or [d s] so that s<d, then d is collapsed to s.
  F  #F by 3 list of face indices into V.
  E  #E by 2 list of edge indices into V.
  EMAP #F*3 list of indices into E, mapping each directed edge to unique unique edge in E
  EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "e=(j->i)
  EI  #E by 2 list of edge flap corners (see above).

Returns
-------
    Returns true if edge collapse is valid

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(edge_collapse_is_valid)
npe_doc(ds_edge_collapse_is_valid)

npe_arg(edge, int)
npe_arg(F, dense_int32, dense_int64)
npe_arg(E, npe_matches(F))
npe_arg(EMAP, npe_matches(F))
npe_arg(EF, npe_matches(F))
npe_arg(EI, npe_matches(F))


npe_begin_code()
  assert_valid_tri_mesh_faces(F);
  assert_cols_equals(E, 2, "E");
  assert_rows_match(F, EMAP, "F", "EMAP");
  assert_cols_equals(EMAP, 3, "EMAP");
  assert_rows_match(E, EI, "E", "EI");
  assert_cols_equals(EI, 2, "EI");
  assert_rows_match(E, EF, "E", "EF");
  assert_cols_equals(EF, 2, "EF");

  const Eigen::MatrixXi F_copy = F.template cast<int>();
  const Eigen::MatrixXi E_copy = E.template cast<int>();
  const Eigen::VectorXi EMAP_copy = EMAP.template cast<int>();
  const Eigen::MatrixXi EF_copy = EF.template cast<int>();
  const Eigen::MatrixXi EI_copy = EI.template cast<int>();

  bool ok = igl::edge_collapse_is_valid(edge, F_copy, E_copy, EMAP_copy, EF_copy, EI_copy);
  return ok;

npe_end_code()

