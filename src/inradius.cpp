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
#include <igl/inradius.h>

const char *ds_inradius = R"igl_Qu8mg5v7(
 Compute the inradius of each triangle in a mesh (V,F)

Parameters
----------
  V  #V by dim list of mesh vertex positions
  F  #F by 3 list of triangle indices into V

Returns
-------
R  #F list of inradii

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(inradius)
npe_doc(ds_inradius)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> r;
  igl::inradius(v, f, r);
  return npe::move(r);

npe_end_code()


