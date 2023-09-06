// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example
//difficult to test

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <pybind11/stl.h>





#include <igl/circulation.h>

const char* ds_circulation = R"igl_Qu8mg5v7(

Return list of faces around the end point of an edge. Assumes
  data-structures are built from an edge-manifold **closed** mesh.

Parameters
----------
e  index into E of edge to circulate
ccw  whether to _continue_ in ccw direction of edge (circulate around
  E(e,1))
EMAP #F*3 list of indices into E, mapping each directed edge to unique
  unique edge in E
EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
  F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
  e=(j->i)
EI  #E by 2 list of edge flap corners (see above).

Returns
-------
Returns list of faces touched by circulation (in cyclically order).

See also
--------

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(circulation)
npe_doc(ds_circulation)

npe_arg(e, int)
npe_arg(ccw, bool)
npe_arg(emap, dense_int32, dense_int64)
npe_arg(ef, npe_matches(emap))
npe_arg(ei, npe_matches(emap))


npe_begin_code()
  assert_cols_equals(ef, 2, "ef");
  assert_cols_equals(ei, 2, "ei");
  assert_shapes_match(ef, ei, "ef", "ei");

      // TODO: remove __copy
      Eigen::VectorXi emap_copy = emap.template cast<int>();
  Eigen::MatrixXi ef_copy = ef.template cast<int>();
  Eigen::MatrixXi ei_copy = ei.template cast<int>();
  auto res = igl::circulation(e, ccw, emap_copy, ef_copy, ei_copy);
  //res is a std::vector
  return res;

npe_end_code()

