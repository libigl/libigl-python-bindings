// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <igl/outer_element.h>

const char *ds_outer_vertex = R"igl_Qu8mg5v7(

Find a vertex that is reachable from infinite without crossing any faces.
Such vertex is called "outer vertex."

Precondition: The input mesh must have all self-intersection resolved and
no duplicated vertices.  See cgal::remesh_self_intersections.h for how to
obtain such input.

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of triangle indices into V
I  #I list of facets to consider

Returns
-------
v_index  index of outer vertex
A  #A list of facets incident to the outer vertex

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(outer_vertex)
npe_doc(ds_outer_vertex)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(i, npe_matches(f))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_cols_equals(i, 1, "i");

  int v_index;
  EigenDenseLike<npe_Matrix_f> a;
  igl::outer_vertex(v, f, i, v_index, a);
  return std::make_tuple(v_index, npe::move(a));

npe_end_code()

const char *ds_outer_edge = R"igl_Qu8mg5v7(

Find an edge that is reachable from infinity without crossing any faces.
   Such edge is called "outer edge."

   Precondition: The input mesh must have all self-intersection resolved and
   no duplicated vertices.  The correctness of the output depends on the fact
   that there is no edge overlap.  See cgal::remesh_self_intersections.h for
   how to obtain such input.

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of triangle indices into V
I  #I list of facets to consider

Returns
-------

v1 index of the first end point of outer edge
v2 index of the second end point of outer edge
A  #A list of facets incident to the outer edge

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(outer_edge)
npe_doc(ds_outer_edge)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(i, npe_matches(f))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_cols_equals(i, 1, "i");

  int v1;
  int v2;
  EigenDenseLike<npe_Matrix_f> a;
  igl::outer_edge(v, f, i, v1, v2, a);
  return std::make_tuple(v1, v2, npe::move(a));

npe_end_code()


const char *ds_outer_facet = R"igl_Qu8mg5v7(

Find a facet that is reachable from infinity without crossing any faces.
Such facet is called "outer facet."

Precondition: The input mesh must have all self-intersection resolved.  I.e
there is no duplicated vertices, no overlapping edge and no intersecting
faces (the only exception is there could be topologically duplicated faces).
See cgal::remesh_self_intersections.h for how to obtain such input.

Parameters
----------
V  #V by 3 list of vertex positions
F  #F by 3 list of triangle indices into V
N  #N by 3 list of face normals
I  #I list of facets to consider

Returns
-------
f  Index of the outer facet.
flipped  true iff the normal of f points inwards.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(outer_facet)
npe_doc(ds_outer_facet)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(n, npe_matches(v))
npe_arg(i, npe_matches(f))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_cols_equals(n, 3, "n");
  assert_rows_match(f, n, "f", "n");
  assert_cols_equals(i, 1, "i");

  int face;
  bool flipped;
  igl::outer_facet(v, f, n, i, face, flipped);
  return std::make_tuple(face, flipped);

npe_end_code()


