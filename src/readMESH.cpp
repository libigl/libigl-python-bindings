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
#include <igl/readMESH.h>

const char* ds_read_mesh = R"igl_Qu8mg5v7(
Load a tetrahedral volume mesh from a .mesh file.

Parameters
----------
filename : path of .mesh file
dtype : data-type of the returned vertices, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------
v : array of vertex positions #v by 3
t : #t by 4 array of tet indices into vertex positions
f : #f by 3 array of face indices into vertex positions

See also
--------
None

Notes
-----
Known bugs: Holes and regions are not supported

Examples
--------
>>> v, t, f = read_mesh("my_mesh.mesh")
)igl_Qu8mg5v7";

npe_function(read_mesh)
npe_doc(ds_read_mesh)
npe_arg(filename, std::string)
npe_default_arg(dtypef, npe::dtype, "float")
npe_begin_code()

  if (dtypef.type() == npe::type_f32) {
    EigenDenseF32 v;
    EigenDenseInt f, t;
    bool ret = igl::readMESH(filename, v, t, f);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(t), npe::move(f));
  } else if (dtypef.type() == npe::type_f64) {
    EigenDenseF64 v;
    EigenDenseInt f, t;
    bool ret = igl::readMESH(filename, v, t, f);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(t), npe::move(f));
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()
