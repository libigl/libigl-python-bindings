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
#include <igl/internal_angles.h>

const char* ds_internal_angles = R"igl_Qu8mg5v7(
Computes internal angles for a triangle mesh.

Parameters
----------
v : #v by dim array of mesh vertex nD positions
f : #f by poly-size array of face (triangle) indices

Returns
-------
k : #f by poly-size array of internal angles. For triangles, columns correspond to edges [1,2],[2,0],[0,1].

See also
--------
None

Notes
-----
If poly-size ≠ 3 then dim must equal 3.

Examples
--------

)igl_Qu8mg5v7";

npe_function(internal_angles)
npe_doc(ds_internal_angles)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)

npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> k;
  igl::internal_angles(v, f, k);
  return npe::move(k);

npe_end_code()
//#include <igl/internal_angles_using_squared_edge_lengths.h>

//const char* ds_internal_angles_using_squared_edge_lengths = R"igl_Qu8mg5v7(

//Parameters
//----------


//Returns
//-------


//See also
//--------


//Notes
//-----
//None

//Examples
//--------

// Inputs:
//     L_sq  #F by 3 list of squared edge lengths
//   Output:
//     K  #F by poly-size eigen Matrix of internal angles
//       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
//
//   Note:
//     Usage of internal_angles_using_squared_edge_lengths is preferred to internal_angles_using_squared_edge_lengths
//)igl_Qu8mg5v7";

//npe_function(internal_angles_using_squared_edge_lengths)
//npe_doc(ds_internal_angles_using_squared_edge_lengths)

//npe_arg(l_sq, dense_float, dense_double)


//npe_begin_code()

//  EigenDense<npe_Scalar_> k;
//  igl::internal_angles_using_squared_edge_lengths(l_sq, k);
//  return npe::move(k);

//npe_end_code()
//#include <igl/internal_angles_using_edge_lengths.h>

//const char* ds_internal_angles_using_edge_lengths = R"igl_Qu8mg5v7(

//Parameters
//----------


//Returns
//-------


//See also
//--------


//Notes
//-----
//None

//Examples
//--------

// Inputs:
//     L  #F by 3 list of edge lengths
//   Output:
//     K  #F by poly-size eigen Matrix of internal angles
//       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
//
//   Note:
//     Usage of internal_angles_using_squared_edge_lengths is preferred to internal_angles_using_squared_edge_lengths
//     This function is deprecated and probably will be removed in future versions
//)igl_Qu8mg5v7";

//npe_function(internal_angles_using_edge_lengths)
//npe_doc(ds_internal_angles_using_edge_lengths)

//npe_arg(l, dense_float, dense_double)


//npe_begin_code()

//  EigenDense<npe_Scalar_> k;
//  igl::internal_angles_using_edge_lengths(l, k);
//  return npe::move(k);

//npe_end_code()


