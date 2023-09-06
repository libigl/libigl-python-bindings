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
#include <igl/piecewise_constant_winding_number.h>







#include <igl/piecewise_constant_winding_number.h>

const char* ds_piecewise_constant_winding_number = R"igl_Qu8mg5v7(

PIECEWISE_CONSTANT_WINDING_NUMBER Determine if a given mesh induces a
   piecewise constant winding number field: Is this mesh valid input to solid
   set operations.  **Assumes** that `(V,F)` contains no self-intersections
   (including degeneracies and co-incidences).  If there are co-planar and
   co-incident vertex placements, a mesh could _fail_ this combinatorial test
   but still induce a piecewise-constant winding number _geometrically_. For
   example, consider a hemisphere with boundary and then pinch the boundary
   "shut" along a line segment. The **_bullet-proof_** check is to first
   resolve all self-intersections in `(V,F) -> (SV,SF)` (i.e. what the
   `igl::copyleft::cgal::piecewise_constant_winding_number` overload does).

Parameters
----------
F  #F by 3 list of triangle indices into some (abstract) list of
  vertices V

Returns
-------
Returns true if the mesh _combinatorially_ induces a piecewise constant
  winding number field.


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(piecewise_constant_winding_number)
npe_doc(ds_piecewise_constant_winding_number)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  return igl::piecewise_constant_winding_number(f);

npe_end_code()


