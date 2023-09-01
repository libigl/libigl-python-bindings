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
#include <igl/readOBJ.h>

const char* ds_read_obj = R"igl_Qu8mg5v7(
Read a mesh from an ascii obj file, filling in vertex positions, normals
and texture coordinates. Only meshes with constant face degree are supported.

Parameters
----------
filename : string, path to .obj file
dtype : data-type of the returned faces, texture coordinates and normals, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------
v : array of vertex positions #v by 3
tc : array of texture coordinats #tc by 2
n : array of corner normals #n by 3
f : #f array of face indices into vertex positions
ftc : #f array of face indices into vertex texture coordinates
fn : #f array of face indices into vertex normals

See also
--------
read_triangle_mesh, read_off

Notes
-----
None

Examples
--------
>>> v, _, n, f, _, _ = read_obj("my_model.obj")
)igl_Qu8mg5v7";

npe_function(read_obj)
npe_doc(ds_read_obj)
npe_arg(filename, std::string)
npe_default_arg(dtype, npe::dtype, "float64")
npe_begin_code()

  if (dtype.type() == npe::type_f32) {
    EigenDenseF32 v, tc, n;
    EigenDenseInt f, ftc, fn;
    bool ret = igl::readOBJ(filename, v, tc, n, f, ftc, fn);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found or containing faces of varying degree (which is not supported yet).");
    }
    return std::make_tuple(npe::move(v), npe::move(tc), npe::move(n), npe::move(f), npe::move(ftc), npe::move(fn));
  } else if (dtype.type() == npe::type_f64) {
    EigenDenseF64 v, tc, n;
    EigenDenseInt f, ftc, fn; // TODO weird problem, int64 gives int128 dtype in numpy
    bool ret = igl::readOBJ(filename, v, tc, n, f, ftc, fn);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found or containing faces of varying degree (which is not supported yet).");
    }
    return std::make_tuple(npe::move(v), npe::move(tc), npe::move(n), npe::move(f), npe::move(ftc), npe::move(fn));
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()
