// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Francis Williams
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <igl/cut_mesh.h>
#include <npe.h>
#include <typedefs.h>

const char* ds_cut_mesh = R"igl_Qu8mg5v7(
Compute the barycenter of every simplex

Parameters
----------
v : #v x dim matrix of vertex coordinates
f : #f x simplex_size  matrix of indices of simplex corners into V
cuts : #F by 3 list of boolean flags, indicating the edges that need to
   be cut (has 1 at the face edges that are to be cut, 0 otherwise)

Returns
-------
A pair (vcut, fcut) where:
  * vcut is a #v by 3 list of the vertex positions
    of the cut mesh. This matrix will be similar to the original vertices except
    some rows will be duplicated.
  * fcut is a #f by 3 list of the faces of the cut mesh (must be triangles). This
    matrix will be similar to the original face matrix except some indices
    will be redirected to point to the newly duplicated vertices.

See also
--------

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(cut_mesh)
npe_doc(ds_cut_mesh)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(cuts, npe_matches(f))
npe_begin_code()
    assert_valid_3d_tri_mesh(v, f);
    assert_shapes_match(f, cuts, "f", "cuts");

    // FIXME: Copying is bad m'kay but libIGL's templates are broken
    EigenDenseLike<npe_Matrix_v> Vcopy = v;
    EigenDenseLike<npe_Matrix_f> Fcopy = f;
    EigenDenseLike<npe_Matrix_cuts> cutsCopy = cuts;

    EigenDenseLike<npe_Matrix_v> Vcut;
    EigenDenseLike<npe_Matrix_f> Fcut;

    igl::cut_mesh(Vcopy, Fcopy, cutsCopy, Vcut, Fcut);

    return std::make_tuple(npe::move(Vcut), npe::move(Fcut));

npe_end_code()
