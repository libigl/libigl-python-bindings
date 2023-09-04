// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/connect_boundary_to_infinity.h>

const char* ds_connect_boundary_to_infinity = R"igl_Qu8mg5v7(

Connect all boundary edges to a fictitious point at infinity.

Parameters
----------
F  #F by 3 list of face indices into some V

Returns
-------
FO  #F+#O by 3 list of face indices into [V;inf inf inf], original F are
  guaranteed to come first. If (V,F) was a manifold mesh, now it is
  closed with a possibly non-manifold vertex at infinity (but it will be
  edge-manifold).

See also
--------

Notes
-----
None

Examples
--------
  
)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity)
npe_doc(ds_connect_boundary_to_infinity)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  EigenDenseLike<npe_Matrix_f> fo;
  igl::connect_boundary_to_infinity(f, fo);
  return npe::move(fo);

npe_end_code()


const char* ds_connect_boundary_to_infinity_face = R"igl_Qu8mg5v7(

Parameters
----------
F  #F by 3 list of face indices into some V

Returns
-------
FO  #F+#O by 3 list of face indices into VO

See also
--------


Notes
-----
None

Examples
--------

   
)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity_face)
npe_doc(ds_connect_boundary_to_infinity_face)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  EigenDenseLike<npe_Matrix_v> vo;
  EigenDenseLike<npe_Matrix_f> fo;
  igl::connect_boundary_to_infinity(v, f, vo, fo);
  return std::make_tuple(npe::move(vo), npe::move(fo));

npe_end_code()







const char* ds_connect_boundary_to_infinity_index = R"igl_Qu8mg5v7(

Parameters
----------
inf_index  index of point at infinity (usually V.rows() or F.maxCoeff())

Returns
-------


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity_index)
npe_doc(ds_connect_boundary_to_infinity_index)

npe_arg(f, dense_int32, dense_int64)
npe_arg(inf_index, int)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  EigenDenseLike<npe_Matrix_f> fo;
  igl::connect_boundary_to_infinity(f, inf_index, fo);
  return npe::move(fo);

npe_end_code()


