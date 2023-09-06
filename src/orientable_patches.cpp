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
#include <igl/orientable_patches.h>

const char* ds_orientable_patches = R"igl_Qu8mg5v7(
Compute connected components of facets connected by manifold edges.

Parameters
----------
f : n by dim array of face ids

Returns
-------
A tuple (c, A) where c is an array of component ids (starting with 0)
and A is a #f x #f adjacency matri

See also
--------
components

Notes
-----
Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches.

Examples
--------

)igl_Qu8mg5v7";

npe_function(orientable_patches)
npe_doc(ds_orientable_patches)
npe_arg(f, dense_int32, dense_int64)
npe_begin_code()

    assert_valid_tri_mesh_faces(f);
    EigenDenseLike<npe_Matrix_f> c;
    EigenSparseLike<npe_Matrix_f> A;
    igl::orientable_patches(f, c, A);
    return std::make_tuple(npe::move(c), npe::move(A));

npe_end_code()

