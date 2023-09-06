// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Daniele Panozzo
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>

// TODO None arguments


#include <igl/writeOFF.h>

const char* ds_write_off = R"igl_Qu8mg5v7(
Export geometry and colors-by-vertex
   Export a mesh from an ascii OFF file, filling in vertex positions.
   Only triangle meshes are supported

Parameters
----------
    str  path to .off output file
     V  #V by 3 mesh vertex positions
     F  #F by 3 mesh indices into V
     C  double matrix of rgb values per vertex #V by 3


Returns
-------
    Returns true on success, false on errors

See also
--------


Notes
-----
None

Examples
--------
   
)igl_Qu8mg5v7";

npe_function(write_off)
npe_doc(ds_write_off)

npe_arg(str, std::string)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(c, npe_matches(v))


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  return igl::writeOFF(str, v, f, c);

npe_end_code()
// #include <igl/writeOFF.h>

// const char* ds_write_off = R"igl_Qu8mg5v7(
// See writeOFF for the documentation.
// )igl_Qu8mg5v7";

// npe_function(write_off)
// npe_doc(ds_write_off)

// npe_arg(str, std::string)
// npe_arg(v, dense_float, dense_double)
// npe_arg(f, dense_int32, dense_int64)


// npe_begin_code()

//   igl::writeOFF(str, v, f);
//   return ;

// npe_end_code()


