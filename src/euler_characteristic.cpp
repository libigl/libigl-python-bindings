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
#include <igl/euler_characteristic.h>

const char* ds_euler_characteristic = R"igl_Qu8mg5v7(

Computes the Euler characteristic of a given mesh (V,F)

Parameters
----------
F #F by dim list of mesh faces (must be triangles)

Returns
-------
Returns An int containing the Euler characteristic

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(euler_characteristic)
npe_doc(ds_euler_characteristic)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  return igl::euler_characteristic(f);

npe_end_code()



