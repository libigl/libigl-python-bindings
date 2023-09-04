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
#include <igl/writeOBJ.h>

const char* ds_write_obj = R"igl_Qu8mg5v7(
Write a mesh in an ascii obj file.

Parameters
----------
filename : path to outputfile
v : array of vertex positions #v by 3
f : #f list of face indices into vertex positions

Returns
-------
ret : bool if output was successful

See also
--------
read_obj

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> success = write_obj(v, f)
)igl_Qu8mg5v7";

npe_function(write_obj)
npe_doc(ds_write_obj)
npe_arg(filename, std::string)
npe_arg(v, dense_double, dense_float)
npe_arg(f, dense_int32, dense_int64)
//npe_default_arg(cn, npe_matches(v), pybind11::array()) TODO: NPE Support none arrays as option
//npe_default_arg(fn, npe_matches(f), pybind11::array())
//npe_default_arg(tc, npe_matches(v), pybind11::array())
//npe_default_arg(ftc, npe_matches(f), pybind11::array())
npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  //return igl::writeOBJ(filename, v, f, cn, fn, tc, ftc);
  return igl::writeOBJ(filename, v, f);

npe_end_code()




