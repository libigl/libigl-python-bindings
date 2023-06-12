// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Sebastian Koch
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>






#include <igl/readDMAT.h>

const char* ds_read_dmat = R"igl_Qu8mg5v7(
Read a matrix from an ascii/binary dmat file, a simple ascii matrix file type, defined as follows. The first line is always:
<#columns> <#rows>
Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

Parameters
----------
filename : string, path to .dmat file
dtype : data-type of the returned matrix. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------
w : array containing read-in coefficients

See also
--------
read_triangle_mesh, read_off

Notes
-----
None

Examples
--------
>>> w = read_dmat("my_model.dmat")
)igl_Qu8mg5v7";

npe_function(read_dmat)
npe_doc(ds_read_dmat)
npe_arg(filename, std::string)
npe_default_arg(dtype, npe::dtype, "float64")
npe_begin_code()

  if (dtype.type() == npe::type_f32) {
    EigenDenseF32 w;
    bool ret = igl::readDMAT(filename, w);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return npe::move(w);
  } else if (dtype.type() == npe::type_f64) {
    EigenDenseF64 w;
    bool ret = igl::readDMAT(filename, w);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return npe::move(w);
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()



