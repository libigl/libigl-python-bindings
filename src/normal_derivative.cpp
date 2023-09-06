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
#include <igl/normal_derivative.h>

const char *ds_normal_derivative = R"igl_Qu8mg5v7(
NORMAL_DERIVATIVE Computes the directional derivative **normal** to
   **all** (half-)edges of a triangle mesh (not just boundary edges). These
   are integrated along the edge: they're the per-face constant gradient dot
   the rotated edge vector (unit rotated edge vector for direction then
   magnitude for integration).

Parameters
----------
    V  #V by dim list of mesh vertex positions
    F  #F by 3|4 list of triangle|tetrahedron indices into V

Returns
-------
    DD  #F*3|4 by #V sparse matrix representing operator to compute
    directional derivative with respect to each facet of each element.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(normal_derivative)
npe_doc(ds_normal_derivative)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tet_or_tri_mesh(v, f);
  //inside there are plenty of MatrixXi...
  Eigen::MatrixXi f_copy = f.template cast<int>();

  EigenSparseLike<npe_Matrix_v> dd;
  igl::normal_derivative(v, f_copy, dd);
  return npe::move(dd);

npe_end_code()


