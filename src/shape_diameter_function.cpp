// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example __miss


#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/shape_diameter_function.h>

const char* ds_shape_diameter_function = R"igl_Qu8mg5v7(

Compute shape diamater function per given point. In the parlence of the
   paper "Consistent Mesh Partitioning and Skeletonisation using the Shape
   Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°
   cone and a _uniform_ average (_not_ a average weighted by inverse angles).

Parameters
----------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of mesh face indices into V
P  #P by 3 list of origin points
N  #P by 3 list of origin normals


Returns
-------
S  #P list of shape diamater function values between bounding box
  diagonal (perfect sphere) and 0 (perfect needle hook)


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(shape_diameter_function)
npe_doc(ds_shape_diameter_function)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(p, npe_matches(v))
npe_arg(n, npe_matches(v))
npe_arg(num_samples, int)

npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  assert_nonzero_rows(p, "p");
  assert_shapes_match(p, n, "p", "n");
  EigenDenseLike<npe_Matrix_v> s;
  igl::shape_diameter_function(v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()


