// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/is_delaunay.h>

const char *ds_is_delaunay = R"igl_Qu8mg5v7(

IS_DELAUNAY Determine if each edge in the mesh (V,F) is Delaunay.


Parameters
----------

V  #V by dim list of vertex positions
F  #F by 3 list of triangles indices

Returns
-------

D  #F by 3 list of bools revealing whether edges corresponding 23 31 12
       are locally Delaunay. Boundary edges are by definition Delaunay.
       Non-Manifold edges are by definition not Delaunay.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(is_delaunay)
npe_doc(ds_is_delaunay)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);

  EigenDense<bool> d;
  igl::is_delaunay(v, f, d);
  return npe::move(d);

npe_end_code()

