// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>






#include <igl/writeDMAT.h>

const char* ds_write_dmat = R"igl_Qu8mg5v7(
Write a matrix from an ascii/binary dmat file, a simple ascii matrix file type, defined as follows. The first line is always:
<#columns> <#rows>
Then the coefficients of the matrix are given separated by whitespace with columns running fastest.

Parameters
----------
filename : string, path to .dmat file
W : m × n matrix
ascii : whether to use ascii format {true}

Returns
-------
ret : whether writing was successful

See also
--------
read_dmat

Notes
-----
None

Examples
--------
>>> write_dmat("my_model.dmat",W,ascii = false)
)igl_Qu8mg5v7";

npe_function(write_dmat)
npe_doc(ds_write_dmat)
npe_arg(filename, std::string)
npe_arg(w, dense_double, dense_float, dense_int32, dense_int64)
npe_default_arg(ascii, bool, true)
npe_begin_code()

return igl::writeDMAT(filename, w, ascii);

npe_end_code()



