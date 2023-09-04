// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example, decide if to remove the first function

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/is_edge_manifold.h>



const char* ds_is_edge_manifold = R"igl_Qu8mg5v7(
See is_edge_manifold for the documentation.
)igl_Qu8mg5v7";

npe_function(is_edge_manifold)
npe_doc(ds_is_edge_manifold)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  return igl::is_edge_manifold(f);

npe_end_code()


