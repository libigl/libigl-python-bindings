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






#include <igl/massmatrix_intrinsic.h>

const char *ds_massmatrix_intrinsic = R"igl_Qu8mg5v7(

Constructs the mass (area) matrix for a given mesh (V,F).


Parameters
----------
l  #l by simplex_size list of mesh edge lengths
F  #F by simplex_size list of mesh elements (triangles or tetrahedra)
type  one of the following ints:
       -igl.MASSMATRIX_TYPE_BARYCENTRIC  barycentric
       -igl.MASSMATRIX_TYPE_VORONOI voronoi-hybrid (default)
       -igl.MASSMATRIX_TYPE_FULL full (not implemented)

Returns
-------
M  #V by #V mass matrix

See also
--------
adjacency_matrix

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(massmatrix_intrinsic)
npe_doc(ds_massmatrix_intrinsic)

npe_arg(l, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(type, int, 1)


npe_begin_code()
  assert_rows_match(l, f, "l", "f");
  assert_cols_equals(l, 3, "l");
  assert_valid_tri_mesh_faces(f);

  static_assert(int(igl::MASSMATRIX_TYPE_BARYCENTRIC) == 0, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_VORONOI) == 1, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_FULL) == 2, "MASSMATRIX enum changed!");
  static_assert(int(igl::MASSMATRIX_TYPE_DEFAULT) == 3, "MASSMATRIX enum changed!");
  static_assert(int(igl::NUM_MASSMATRIX_TYPES) == 4, "MASSMATRIX enum changed!");

  if (type >= igl::NUM_MASSMATRIX_TYPES )
  {
    std::string errmsg =
        std::string("Invalid enum for type should be in the range 0 to ") +
        std::to_string(igl::NUM_MASSMATRIX_TYPES - 1);
    throw pybind11::value_error(errmsg);
  }

  Eigen::SparseMatrix<npe_Scalar_l> m;
  igl::massmatrix_intrinsic(l, f, igl::MassMatrixType(type), m);
  return npe::move(m);

npe_end_code()
