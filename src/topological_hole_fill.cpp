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

#include <pybind11/stl.h>

#include <igl/topological_hole_fill.h>

const char *ds_topological_hole_fill = R"igl_Qu8mg5v7(

Topological fill hole on a mesh, with one additional vertex each hole
Index of new abstract vertices will be F.maxCoeff() + (index of hole)

Parameters
----------

F  #F by simplex-size list of element indices
holes vector of hole loops to fill

Returns
-------
F_filled  input F stacked with filled triangles.

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(topological_hole_fill)
npe_doc(ds_topological_hole_fill)

npe_arg(f, dense_int32, dense_int64)
npe_arg(holes, std::vector<std::vector<int>>)


npe_begin_code()

  EigenDense<npe_Scalar_f> f_filled;
  igl::topological_hole_fill(f, holes, f_filled);
  return npe::move(f_filled);

npe_end_code()
