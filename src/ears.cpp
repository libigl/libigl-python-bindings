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
#include <igl/ears.h>

const char* ds_ears = R"igl_Qu8mg5v7(
FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh
Parameters
----------
F  #F by 3 list of triangle mesh indices

Returns
-------
     ears  #ears list of indices into F of ears
     ear_opp  #ears list of indices indicating which edge is non-boundary
       (connecting to flops)

See also
--------


Notes
-----
None

Examples
--------
   ears,ear_opp = find_ears(F)

)igl_Qu8mg5v7";

npe_function(ears)
npe_doc(ds_ears)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  Eigen::Matrix<npe_Scalar_f,Eigen::Dynamic,1> ear;
  Eigen::Matrix<npe_Scalar_f,Eigen::Dynamic,1> ear_opp;
  igl::ears(f, ear, ear_opp);
  return std::make_tuple(npe::move(ear), npe::move(ear_opp));

npe_end_code()


