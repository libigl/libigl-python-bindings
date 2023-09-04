// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/cgal/intersect_other.h>



const char* ds_intersect_other = R"igl_Qu8mg5v7(
INTERSECT_OTHER Given a triangle mesh (VA,FA) and another mesh (VB,FB) find all
pairs of intersecting faces. Note that self-intersections are ignored.
      

Parameters
----------
VA  : #VA by 3 list of vertex positions of first mesh
FA  : #FA by 3 list of triangle indices into VA
VB  : #VB by 3 list of vertex positions of second mesh
FB  : #FB by 3 list of triangle indices into VB
detect_only : avoid constructing intersections results when possible  {false}
first_only  : return after detecting the first intersection (if
  first_only==true, then detect_only should also be true) {false}
stitch_all  : whether to stitch all resulting constructed elements into a
  (non-manifold) mesh  {false}
slow_and_more_precise_rounding  : whether to use slow and more precise
  rounding (see assign_scalar) {false}


Returns
-------
IF : #intersecting face pairs by 2  list of intersecting face pairs, indexing F
VVAB : #VVAB by 3 list of vertex positions
FFAB : #FFAB by 3 list of triangle indices into VVAB
JAB  : #FFAB list of indices into [FA;FB] denoting birth triangle
IMAB :  #VVAB list of indices stitching duplicates (resulting from
  mesh intersections) together
      
See also
--------
mesh_boolean
)igl_Qu8mg5v7";

npe_function(intersect_other)
npe_doc(  ds_intersect_other)

npe_arg(VA, dense_float, dense_double)
npe_arg(FA, dense_int32, dense_int64)
npe_arg(VB, npe_matches(VA))
npe_arg(FB, npe_matches(FA))
npe_default_arg(detect_only, bool, false)
npe_default_arg(first_only, bool, false)
npe_default_arg(stitch_all, bool, false)
// Awaiting bump in libigl
//npe_default_arg(slow_and_more_precise_rounding, bool, false)


npe_begin_code()
  Eigen::MatrixXd VAcpy = VA.template cast<double>();
  Eigen::MatrixXi FAcpy = FA.template cast<int>();
  Eigen::MatrixXd VBcpy = VB.template cast<double>();
  Eigen::MatrixXi FBcpy = FB.template cast<int>();

  Eigen::MatrixXd VVABcpy;
  Eigen::MatrixXi FFABcpy;
  Eigen::VectorXi  JABcpy;
  Eigen::VectorXi IMABcpy;
  Eigen::MatrixXi IFcpy;
  igl::copyleft::cgal::RemeshSelfIntersectionsParam params;
  params.detect_only = detect_only;
  params.first_only = first_only;
  params.stitch_all = stitch_all;
  //params.slow_and_more_precise_rounding = slow_and_more_precise_rounding;
  igl::copyleft::cgal::intersect_other(
    VAcpy,FAcpy,VBcpy,FBcpy,params,IFcpy,VVABcpy,FFABcpy,JABcpy,IMABcpy);

  EigenDenseLike<npe_Matrix_FA> IF   =   IFcpy.cast<typename decltype(IF  )::Scalar>();
  EigenDenseLike<npe_Matrix_VA> VVAB = VVABcpy.cast<typename decltype(VVAB)::Scalar>();
  EigenDenseLike<npe_Matrix_FA> FFAB = FFABcpy.cast<typename decltype(FFAB)::Scalar>();
  EigenDenseLike<npe_Matrix_FA>  JAB =  JABcpy.cast<typename decltype( JAB)::Scalar>();
  EigenDenseLike<npe_Matrix_FA> IMAB = IMABcpy.cast<typename decltype(IMAB)::Scalar>();
  return std::make_tuple(
    npe::move(IF), 
    npe::move(VVAB), 
    npe::move(FFAB), 
    npe::move( JAB), 
    npe::move(IMAB));
npe_end_code()


