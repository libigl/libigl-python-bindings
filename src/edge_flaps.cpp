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

#include <igl/edge_flaps.h>

const char *ds_edge_flaps = R"igl_Qu8mg5v7(

Determine "edge flaps": two faces on either side of a unique edge (assumes edge-manifold mesh)


Parameters
----------

F  #F by 3 list of face indices

Returns
-------

E  #E by 2 list of edge indices into V.
EMAP #F*3 list of indices into E, mapping each directed edge to unique
  unique edge in E
EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
  F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
  e=(j->i)
EI  #E by 2 list of edge flap corners (see above).

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(edge_flaps)
npe_doc(ds_edge_flaps)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tri_mesh_faces(f);

  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXi e_copy;
  Eigen::VectorXi emap_copy;
  Eigen::MatrixXi ef_copy;
  Eigen::MatrixXi ei_copy;
  igl::edge_flaps(f_copy, e_copy, emap_copy, ef_copy, ei_copy);

  EigenDense<npe_Scalar_f> e = e_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> emap = emap_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> ef = ef_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> ei = ei_copy.template cast<npe_Scalar_f>();
  return std::make_tuple(npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei));

npe_end_code()


