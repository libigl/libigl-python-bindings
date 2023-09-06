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
#include <igl/bone_parents.h>

const char* ds_bone_parents = R"igl_Qu8mg5v7(
BONE_PARENTS Recover "parent" bones from directed graph representation.
Parameters
----------
BE  #BE by 2 list of directed bone edges

Returns
-------
P  #BE by 1 list of parent indices into BE, -1 means root.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(bone_parents)
npe_doc(ds_bone_parents)

npe_arg(be, dense_int32, dense_int64)


npe_begin_code()
  assert_cols_equals(be, 2, "be");
  EigenDenseLike<npe_Matrix_be> p;
  igl::bone_parents(be, p);
  return npe::move(p);

npe_end_code()


