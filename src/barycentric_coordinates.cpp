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
#include <igl/barycentric_coordinates.h>
#include <iostream>
const char* ds_barycentric_coordinates_tet = R"igl_Qu8mg5v7(

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is
`a[i, :], b[i, :], c[i, :], d[:, i]`.

Parameters
----------
p : #P by 3 Query points in 3d
a : #P by 3 Tet corners in 3d
b : #P by 3 Tet corners in 3d
c : #P by 3 Tet corners in 3d
d : #P by 3 Tet corners in 3d

Returns
-------
#P by 4 list of barycentric coordinates

See also
--------

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(barycentric_coordinates_tet)
npe_doc(ds_barycentric_coordinates_tet)
npe_arg(p, dense_float, dense_double)
npe_arg(a, npe_matches(p))
npe_arg(b, npe_matches(p))
npe_arg(c, npe_matches(p))
npe_arg(d, npe_matches(p))
npe_begin_code()

    assert_rows_match(p, a, "p", "a");
    assert_rows_match(p, b, "p", "b");
    assert_rows_match(p, c, "p", "c");
    assert_rows_match(p, d, "p", "d");
    assert_cols_equals(p, 3, "p");
    assert_cols_equals(a, 3, "a");
    assert_cols_equals(b, 3, "b");
    assert_cols_equals(c, 3, "c");
    assert_cols_equals(d, 3, "d");
    EigenDenseLike<npe_Matrix_p> l;
    igl::barycentric_coordinates(p, a, b, c, d, l);
    return npe::move(l);

npe_end_code()





const char* ds_barycentric_coordinates_tri = R"igl_Qu8mg5v7(

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is
`a[i, :], b[i, :], c[i, :]`.

Parameters
----------
p : #P by 3 Query points in 3d
a : #P by 3 Tri corners in 3d
b : #P by 3 Tri corners in 3d
c : #P by 3 Tri corners in 3d

Returns
-------
#P by 3 list of barycentric coordinates

See also
--------

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(barycentric_coordinates_tri)
npe_doc(ds_barycentric_coordinates_tri)
npe_arg(p, dense_float, dense_double)
npe_arg(a, npe_matches(p))
npe_arg(b, npe_matches(p))
npe_arg(c, npe_matches(p))
npe_begin_code()
    assert_rows_match(p, a, "p", "a");
    assert_rows_match(p, b, "p", "b");
    assert_rows_match(p, c, "p", "c");
    assert_cols_equals(p, 3, "p");
    assert_cols_equals(a, 3, "a");
    assert_cols_equals(b, 3, "b");
    assert_cols_equals(c, 3, "c");

    EigenDenseLike<npe_Matrix_p> l;
    igl::barycentric_coordinates(p, a, b, c, l);
    return npe::move(l);

npe_end_code()
