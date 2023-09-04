// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <common.h>
#include <igl/hessian.h>

const char *ds_hessian = R"igl_Qu8mg5v7(
 Constructs the finite element Hessian matrix
     as described in https:arxiv.org/abs/1707.04348,
     Natural Boundary Conditions for Smoothing in Geometry Processing
     (Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)
     The interior vertices are NOT set to zero yet.

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh faces (must be triangles)

Returns
-------
H  #V by #V Hessian energy matrix, each column i corresponding to V(i,:)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(hessian)
npe_doc(ds_hessian)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);
  EigenSparseLike<npe_Matrix_v> h;
  igl::hessian(v, f, h);
  return npe::move(h);
npe_end_code()


