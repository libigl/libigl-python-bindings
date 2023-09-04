// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <igl/adjacency_list.h>
#include <pybind11/stl.h>

const char* ds_adjacency_list = R"igl_Qu8mg5v7(
Constructs the graph adjacency list of a given mesh (v, f)

Parameters
----------
f : #f by dim array of fixed dimensional (e.g. triangle (#f by 3),
    tet (#f by 4), quad (#f by 4), etc...) mesh faces

Returns
-------
list of lists containing at index i the adjacent vertices of vertex i

See also
--------
adjacency_matrix

Notes
-----

Examples
--------
# Mesh in (v, f)
>>> a = mesh_adjacency_list(f)
)igl_Qu8mg5v7";

npe_function(adjacency_list)
npe_doc(ds_adjacency_list)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f, "f");
  std::vector<std::vector<npe_Scalar_f>> a;
  igl::adjacency_list(f, a);
  return pybind11::detail::type_caster<decltype(a)>::cast(a, pybind11::return_value_policy::move, pybind11::none());

npe_end_code()
