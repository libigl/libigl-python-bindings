// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Nico
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/facet_components.h>

const char* ds_facet_components = R"igl_Qu8mg5v7(
Compute connected components of facets based on edge-edge adjacency,

Parameters
----------
f : #f x 3 array of triangle indices

Returns
-------
An array, c, with shape (#f,), of component ids

See also
--------
vertex_components
vertex_components_from_adjacency_matrix

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(facet_components)
npe_doc(ds_facet_components)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()
    assert_valid_tri_mesh_faces(f);
    EigenDenseLike<npe_Matrix_f> c;
    igl::facet_components(f, c);
    return npe::move(c);
npe_end_code()
