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


#include <igl/triangulated_grid.h>

const char *ds_triangulated_grid = R"igl_Qu8mg5v7(

Create a regular grid of elements (only 2D supported, currently)
   Vertex position order is compatible with `igl::grid`

Parameters
----------
nx  number of vertices in the x direction
ny  number of vertices in the y direction

Returns
-------

GV  nx*ny by 2 list of mesh vertex positions.
GF  2*(nx-1)*(ny-1) by 3  list of triangle indices

See also
--------
grid, quad_grid

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(triangulated_grid)
npe_doc(ds_triangulated_grid)

npe_arg(nx, int)
npe_arg(ny, int)


npe_begin_code()

  EigenDenseFloat gv;
  EigenDenseInt gf;
  igl::triangulated_grid(nx, ny, gv, gf);
  return std::make_tuple(npe::move(gv), npe::move(gf));

npe_end_code()
