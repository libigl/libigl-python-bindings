// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <igl/triangles_from_strip.h>

const char *ds_triangles_from_strip = R"igl_Qu8mg5v7(

TRIANGLES_FROM_STRIP Create a list of triangles from a stream of indices
   along a strip.

Parameters
----------
S  #S list of indices

Returns
-------
F  #S-2 by 3 list of triangle indices

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(triangles_from_strip)
npe_doc(ds_triangles_from_strip)

npe_arg(s, dense_int32, dense_int64)


npe_begin_code()
  Eigen::Matrix<npe_Scalar_s, Eigen::Dynamic, 1> s_copy(s.size());

  for(int i = 0; i < s_copy.size(); ++i)
  {
    if(s.cols() == 1)
      s_copy(i) = s(i, 0);
    else if (s.rows() == 1)
      s_copy(i) = s(0, i);
    else
      throw std::invalid_argument("Input s must have rows or cols equal to 1");
  }

  EigenDense<npe_Scalar_s> f;
  igl::triangles_from_strip(s_copy, f);
  return npe::move(f);

npe_end_code()


