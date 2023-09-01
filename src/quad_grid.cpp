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


#include <igl/quad_grid.h>

const char *ds_quad_grid = R"igl_Qu8mg5v7(

Generate a quad mesh over a regular grid.

Parameters
----------
nx  number of vertices in the x direction
ny  number of vertices in the y direction


Returns
-------

V  nx*ny by 2 list of vertex positions
Q  (nx-1)*(ny-1) by 4 list of quad indices into V
E  (nx-1)*ny+(ny-1)*nx by 2 list of undirected quad edge indices into V

See also
--------
grid, triangulated_grid

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(quad_grid)
npe_doc(ds_quad_grid)

npe_arg(nx, int)
npe_arg(ny, int)


npe_begin_code()

  EigenDenseFloat gv;
  EigenDenseInt gf;
  EigenDenseInt e;
  igl::quad_grid(nx, ny, gv, gf, e);
  return std::make_tuple(npe::move(gv), npe::move(gf), npe::move(e));

npe_end_code()
