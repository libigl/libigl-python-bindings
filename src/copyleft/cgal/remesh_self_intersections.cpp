// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/cgal/remesh_self_intersections.h>



const char* ds_remesh_self_intersections = R"igl_Qu8mg5v7(
REMESH_SELF_INTERSECTIONS Given a triangle mesh (V,F) compute a new mesh (VV,FF)
which is the same as (V,F) except that any self-intersecting triangles in (V,F)
have been subdivided (new vertices and face created) so that the
self-intersection contour lies exactly on edges in (VV,FF). New vertices will
appear in original faces or on original edges. New vertices on edges are
"merged" only across original faces sharing that edge. This means that if the
input triangle mesh is a closed manifold the output will be too.
      

Parameters
----------
V  : #V by 3 list of vertex positions of mesh
F  : #F by 3 list of triangle indices into rows of V
detect_only : avoid constructing intersections results when possible  {false}
first_only  : return after detecting the first intersection (if
  first_only==true, then detect_only should also be true) {false}
stitch_all  : whether to stitch all resulting constructed elements into a
  (non-manifold) mesh  {false}
slow_and_more_precise_rounding  : whether to use slow and more precise
  rounding (see assign_scalar) {false}


Returns
-------
VV : #VV by 3 list of vertex positions
FF : #FF by 3 list of triangle indices into VV
IF : #intersecting face pairs by 2  list of intersecting face pairs, indexing F
J  : #FF list of indices into F denoting birth triangle
IM : #VV list of indices into VV of unique vertices.
      
See also
--------
mesh_boolean
)igl_Qu8mg5v7";

npe_function(remesh_self_intersections)
npe_doc(ds_remesh_self_intersections)

npe_arg(V, dense_float, dense_double)
npe_arg(F, dense_int, dense_long, dense_longlong)
npe_default_arg(detect_only, bool, false)
npe_default_arg(first_only, bool, false)
npe_default_arg(stitch_all, bool, false)
// Awaiting bump in libigl
//npe_default_arg(slow_and_more_precise_rounding, bool, false)


npe_begin_code()
  Eigen::MatrixXd Vcpy = V.template cast<double>();
  Eigen::MatrixXi Fcpy = F.template cast<int>();

  Eigen::MatrixXd VVcpy;
  Eigen::MatrixXi FFcpy;
  Eigen::VectorXi  Jcpy;
  Eigen::VectorXi IMcpy;
  Eigen::MatrixXi IFcpy;
  igl::copyleft::cgal::RemeshSelfIntersectionsParam params;
  params.detect_only = detect_only;
  params.first_only = first_only;
  params.stitch_all = stitch_all;
  //params.slow_and_more_precise_rounding = slow_and_more_precise_rounding;
  igl::copyleft::cgal::remesh_self_intersections(
    Vcpy,Fcpy,params,VVcpy,FFcpy,IFcpy,Jcpy,IMcpy);

  EigenDenseLike<npe_Matrix_V> VV = VVcpy.cast<typename decltype(VV)::Scalar>();
  EigenDenseLike<npe_Matrix_F> FF = FFcpy.cast<typename decltype(FF)::Scalar>();
  EigenDenseLike<npe_Matrix_F> IF = IFcpy.cast<typename decltype(IF)::Scalar>();
  EigenDenseLike<npe_Matrix_F>  J =  Jcpy.cast<typename decltype( J)::Scalar>();
  EigenDenseLike<npe_Matrix_F> IM = IMcpy.cast<typename decltype(IM)::Scalar>();
  return std::make_tuple(npe::move(VV), npe::move(FF), npe::move(IF), npe::move(J), npe::move(IM));
npe_end_code()
