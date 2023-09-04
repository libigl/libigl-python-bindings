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
#include <igl/per_vertex_attribute_smoothing.h>

const char* ds_per_vertex_attribute_smoothing = R"igl_Qu8mg5v7(

Smooth vertex attributes using uniform Laplacian

Parameters
----------
Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)
F    #F by 3 eigne Matrix of face (triangle) indices

Returns
-------
Aout #V by #A eigen Matrix of mesh vertex attributes

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(per_vertex_attribute_smoothing)
npe_doc(ds_per_vertex_attribute_smoothing)

npe_arg(ain, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_3d_tri_mesh(ain, f);
  // remove __copy
  Eigen::MatrixXd ain_copy = ain.template cast<double>();
  Eigen::MatrixXd aout;
  igl::per_vertex_attribute_smoothing(ain_copy, f, aout);
  EigenDenseFloat aout_row_major = aout;
  return npe::move(aout_row_major);

npe_end_code()


