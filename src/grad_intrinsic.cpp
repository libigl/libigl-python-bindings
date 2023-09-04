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






#include <igl/grad_intrinsic.h>

const char *ds_grad_intrinsic = R"igl_Qu8mg5v7(

GRAD_INTRINSIC Construct an intrinsic gradient operator.


Parameters
----------

l  #F by 3 list of edge lengths
F  #F by 3 list of triangle indices into some vertex list V

Returns
-------
G  #F*2 by #V gradient matrix: G=[Gx;Gy] where x runs along the 23 edge and
      y runs in the counter-clockwise 90° rotation.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(grad_intrinsic)
npe_doc(ds_grad_intrinsic)

npe_arg(l, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_rows_match(l, f, "l", "f");
  assert_cols_equals(l, 3, "l");
  assert_valid_tri_mesh_faces(f);

  EigenDense<npe_Scalar_f> f_copy = f;

  Eigen::SparseMatrix<npe_Scalar_l> g;
  igl::grad_intrinsic(l, f_copy, g);
  return npe::move(g);

npe_end_code()


