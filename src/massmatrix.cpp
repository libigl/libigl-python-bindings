// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/massmatrix.h>

const char* ds_massmatrix = R"igl_Qu8mg5v7(
Constructs the mass (area) matrix for a given mesh (V,F).

Parameters
----------
v : #v by dim list of mesh vertex positions
f : #f by simplex_size list of mesh faces (must be triangles)
type : one of the following types:
       -igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric
       -igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)
       -igl.MASSMATRIX_TYPE_FULL full (not implemented)

Returns
-------
m : #v by #v mass matrix

See also
--------
adjacency_matrix, cotmatrix, grad

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(massmatrix)
npe_doc(ds_massmatrix)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(type, int, 3)
npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  static_assert(int(igl::MASSMATRIX_TYPE_BARYCENTRIC) == 0, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_VORONOI) == 1, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_FULL) == 2, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_DEFAULT) == 3, "MASSMATRIX enum changed!");
  static_assert(int(igl::NUM_MASSMATRIX_TYPES) == 4, "MASSMATRIX enum changed!");

  if (type >= igl::NUM_MASSMATRIX_TYPES ) {
    std::string errmsg =
        std::string("Invalid enum for type should be in the range 0 to ") +
        std::to_string(igl::NUM_MASSMATRIX_TYPES-1);
    throw pybind11::value_error(errmsg);
  }

  EigenSparseLike<npe_Matrix_v> m;
  igl::massmatrix(v, f, igl::MassMatrixType(type), m);
  return npe::move(m);

npe_end_code()


