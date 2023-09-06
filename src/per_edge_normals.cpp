// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __miss __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/per_edge_normals.h>

const char* ds_per_edge_normals = R"igl_Qu8mg5v7(

Compute face normals via vertex position list, face list

Parameters
----------
V  #V by 3 eigen Matrix of mesh vertex 3D positions
F  #F by 3 eigen Matrix of face (triangle) indices
weight  weighting type
FN  #F by 3 matrix of 3D face normals per face


Returns
-------
N  #2 by 3 matrix of mesh edge 3D normals per row
E  #E by 2 matrix of edge indices per row
EMAP  #E by 1 matrix of indices from all edges to E


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(per_edge_normals)
npe_doc(ds_per_edge_normals)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(weight, int , 0)
npe_arg(fn, npe_matches(v))


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> n;
  EigenDenseLike<npe_Matrix_f> e;
  Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> emap;
  igl::per_edge_normals(v, f, igl::PerEdgeNormalsWeightingType(weight), fn, n, e, emap);
  return std::make_tuple(npe::move(n), npe::move(e), npe::move(emap));

npe_end_code()


