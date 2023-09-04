// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <pybind11/stl.h>

#include <npe.h>
#include <typedefs.h>

#include <igl/triangle/triangulate.h>

const char* ds_triangulate = R"igl_Qu8mg5v7(
Triangulate the interior of a polygon using the triangle library.

Parameters
----------
  V : #V by 2 list of 2D vertex positions
  E : #E by 2 list of vertex ids forming unoriented edges of the boundary of the polygon
  H : #H by 2 coordinates of points contained inside holes of the polygon
  flags  : string of options pass to triangle (see triangle documentation)
Returns
--------
  V2  #V2 by 2  coordinates of the vertives of the generated triangulation
  F2  #F2 by 3  list of indices forming the faces of the generated triangulation

)igl_Qu8mg5v7";

npe_function(triangulate)
npe_doc(ds_triangulate)

npe_arg(V, dense_float, dense_double)
npe_arg(E, dense_int32, dense_int64)
npe_default_arg(H, npe_matches(V) ,pybind11::array())
npe_default_arg(flags, std::string, "")
npe_default_arg(VM, npe_matches(E), pybind11::array())
npe_default_arg(EM, npe_matches(E), pybind11::array())
npe_begin_code()

EigenDenseLike<npe_Matrix_V> V2;
EigenDenseLike<npe_Matrix_E> F2;
EigenDenseLike<npe_Matrix_E> VM2,E2,EM2;
using V2Type = decltype(V2);
using F2Type = decltype(F2);
using VM2Type = decltype(VM2);
using E2Type = decltype(E2);
using EM2Type = decltype(EM2);
if(VM.size() == 0 && EM.size() == 0)
{
  igl::triangle::triangulate(V, E, H, flags, V2, F2);
  return std::list<pybind11::object>({npe::move(V2), npe::move(F2)});
}else
{
  igl::triangle::triangulate(V, E, H, VM.reshaped(), EM.reshaped(), flags, V2, F2, VM2, E2, EM2);
  if(VM.size() && EM.size())
  {
    return std::list<pybind11::object>({npe::move(V2), npe::move(F2), npe::move(VM2), npe::move(E2), npe::move(EM2)});
  }else if(VM.size())
  {
    return std::list<pybind11::object>({npe::move(V2), npe::move(F2), npe::move(VM2)});
  }else
  {
    return std::list<pybind11::object>({npe::move(V2), npe::move(F2), npe::move(E2), npe::move(EM2)});
  }
}

npe_end_code()

