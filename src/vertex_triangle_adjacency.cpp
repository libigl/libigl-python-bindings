// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __miss __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/vertex_triangle_adjacency.h>

const char* ds_vertex_triangle_adjacency = R"igl_Qu8mg5v7(

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

Parameters
----------
F  #F by 3 list of triangle indices into some vertex list V
n  number of vertices, #V (e.g., F.maxCoeff()+1)

Returns
-------
VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =
  f, means that face f is the jth face (in no particular order) incident
  on vertex i.
NI  #V+1 list  cumulative sum of vertex-triangle degrees with a
  preceeding zero. "How many faces" have been seen before visiting this
  vertex and its incident faces.


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(vertex_triangle_adjacency)
npe_doc(ds_vertex_triangle_adjacency)

npe_arg(f, dense_int32, dense_int64)
npe_arg(n, int)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  Eigen::VectorXi vf;
  Eigen::VectorXi ni;
  igl::vertex_triangle_adjacency(f, n, vf, ni);
  return std::make_tuple(npe::move(vf), npe::move(ni));

npe_end_code()



