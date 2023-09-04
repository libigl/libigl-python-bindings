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
#include <igl/intrinsic_delaunay_cotmatrix.h>

const char *ds_intrinsic_delaunay_cotmatrix = R"igl_Qu8mg5v7(

INTRINSIC_DELAUNAY_COTMATRIX Computes the discrete cotangent Laplacian of a
mesh after converting it into its intrinsic Delaunay triangulation (see,
e.g., [Fisher et al. 2007].

Parameters
----------

V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh elements (triangles or tetrahedra)

Returns
-------

L  #V by #V cotangent matrix, each row i corresponding to V(i,:)
l_intrinsic  #F by 3 list of intrinsic edge-lengths used to compute L
F_intrinsic  #F by 3 list of intrinsic face indices used to compute L

See also
--------
intrinsic_delaunay_triangulation, cotmatrix, cotmatrix_intrinsic

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_cotmatrix)
npe_doc(ds_intrinsic_delaunay_cotmatrix)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  Eigen::SparseMatrix<npe_Scalar_v> l;
  EigenDense<npe_Scalar_v> l_intrinsic;
  EigenDense<npe_Scalar_f> f_intrinsic;
  igl::intrinsic_delaunay_cotmatrix(v, f, l, l_intrinsic, f_intrinsic);
  return std::make_tuple(npe::move(l), npe::move(l_intrinsic), npe::move(f_intrinsic));

npe_end_code()

