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






#include <igl/hausdorff.h>

const char *ds_hausdorff = R"igl_Qu8mg5v7(

 HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh
   (VB,FB). This is the

   d(A,B) = max ( max min d(a,b) , max min d(b,a) )
                  a∈A b∈B          b∈B a∈A

Parameters
----------
     VA  #VA by 3 list of vertex positions
     FA  #FA by 3 list of face indices into VA
     VB  #VB by 3 list of vertex positions
     FB  #FB by 3 list of face indices into VB

Returns
-------
    d  hausdorff distance
    pair  2 by 3 list of "determiner points" so that pair(1,:) is from A
    and pair(2,:) is from B

See also
--------


Notes
-----
   Known issue: This is only computing max(min(va,B),min(vb,A)). This is
   better than max(min(va,Vb),min(vb,Va)). This (at least) is missing
   "edge-edge" cases like the distance between the two different
   triangulations of a non-planar quad in 3D. Even simpler, consider the
   Hausdorff distance between the non-convex, block letter V polygon (with 7
   vertices) in 2D and its convex hull. The Hausdorff distance is defined by
   the midpoint in the middle of the segment across the concavity and some
   non-vertex point _on the edge_ of the V.

Examples
--------
)igl_Qu8mg5v7";

npe_function(hausdorff)
npe_doc(ds_hausdorff)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_int32, dense_int64)
npe_arg(vb, npe_matches(va))
npe_arg(fb, npe_matches(fa))


npe_begin_code()
    assert_valid_3d_tri_mesh(va, fa, "va", "fa");
    assert_valid_3d_tri_mesh(vb, fb, "vb", "fb");

  double d;
  igl::hausdorff(va, fa, vb, fb, d);
  return d;

npe_end_code()



