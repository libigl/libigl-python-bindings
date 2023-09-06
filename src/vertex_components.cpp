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
#include <igl/vertex_components.h>

const char* ds_vertex_components = R"igl_Qu8mg5v7(
Compute connected components of the vertices of a mesh given the mesh' face indices.

Parameters
----------
f : #f x dim array of face indices

Returns
-------
An array of component ids (starting with 0)

See also
--------
vertex_components_from_adjacency_matrix
facet_components

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(vertex_components)
npe_doc(ds_vertex_components)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()
    assert_valid_tri_mesh_faces(f);
    EigenDenseLike<npe_Matrix_f> c;
    igl::vertex_components(f, c);
    return npe::move(c);
npe_end_code()


const char* ds_vertex_components_from_adjacency_matrix = R"igl_Qu8mg5v7(
Compute connected components of a graph represented by a sparse adjacency
matrix.

Parameters
----------
a : n by n sparse adjacency matrix

Returns
-------
A tuple (c, counts) where c is an array of component ids (starting with 0)
and counts is a #components array of counts for each component

See also
--------
vertex_components
facet_components

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(vertex_components_from_adjacency_matrix)
npe_doc(ds_vertex_components_from_adjacency_matrix)
npe_arg(a, sparse_int32, sparse_int64)
npe_begin_code()
    EigenDense<npe_Scalar_a> c;
    EigenDense<npe_Scalar_a> counts;
    igl::vertex_components(a, c, counts);
    return std::make_tuple(npe::move(c), npe::move(counts));
npe_end_code()



