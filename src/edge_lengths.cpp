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
#include <igl/edge_lengths.h>

const char *ds_edge_lengths = R"igl_Qu8mg5v7(


 Constructs a list of lengths of edges opposite each index in a face
   (triangle/tet) list

Parameters
----------
V  eigen matrix #V by 3
F  #F by 2 list of mesh edges or
F  #F by 3 list of mesh faces (must be triangles) or
T  #T by 4 list of mesh elements (must be tets)

Returns
-------
L  #F by {1|3|6} list of edge lengths
       for edges, column of lengths
       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
       for tets, columns correspond to edges
       [3 0],[3 1],[3 2],[1 2],[2 0],[0 1]

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(edge_lengths)
npe_doc(ds_edge_lengths)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_cols_equals(v, 3, "V");
  assert_nonzero_rows(v, "V");
  assert_nonzero_rows(f, "F");

  const auto dim = f.cols();
  if(dim != 2 && dim != 3 && dim != 4)
    throw pybind11::value_error("Invalid dimension for F must be 2, 3, or 4 but got " + std::to_string(dim));

  EigenDenseLike<npe_Matrix_v> l;
  igl::edge_lengths(v, f, l);
  return npe::move(l);

npe_end_code()


