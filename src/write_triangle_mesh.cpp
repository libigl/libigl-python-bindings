// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>


#include <igl/write_triangle_mesh.h>
#include <igl/FileEncoding.h>

const char *ds_write_triangle_mesh = R"igl_Qu8mg5v7(
 write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

Parameters
----------
    str  path to file
     V  double matrix #V by 3
     F  int matrix #F by 3
    force_ascii=True  force ascii format even if binary is available
Returns
-------
    Returns true iff success

See also
--------


Notes
-----


Examples
--------

)igl_Qu8mg5v7";

npe_function(write_triangle_mesh)
npe_doc(ds_write_triangle_mesh)

npe_arg(str, std::string)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(force_ascii, bool, bool(true))

npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  // TODO: remove __copy
  //copy is necessary for the ply library
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd v_copy = v.template cast<double>();
  
  igl::FileEncoding encoding = igl::FileEncoding::Ascii;
  if (!force_ascii) {
    //NOTE: if not ascii, we default to binary
    encoding = igl::FileEncoding::Binary;
  }

  bool ok = igl::write_triangle_mesh(str, v_copy, f_copy, encoding);
  return ok;

npe_end_code()


