// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/boundary_facets.h>

const char* ds_boundary_facets = R"igl_Qu8mg5v7(
Determine boundary faces (edges) of tetrahedra (triangles).

Parameters
----------
t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles

Returns
-------
f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges

See also
--------
None

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> b = boundary_facets(f)
)igl_Qu8mg5v7";

npe_function(boundary_facets)
npe_doc(ds_boundary_facets)
npe_arg(t, dense_int32, dense_int64)
npe_begin_code()

  assert_valid_tet_or_tri_mesh_faces(t, "t");
  EigenDense<npe_Scalar_t> f;
  igl::boundary_facets(t, f);
  return npe::move(f);

npe_end_code()

