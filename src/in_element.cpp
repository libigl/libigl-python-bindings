// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/in_element.h>
#include <igl/AABB.h>

using AABB_f64_3 = igl::AABB<Eigen::Map<const Eigen::MatrixXd>,3>;
using AABB_f64_2 = igl::AABB<Eigen::Map<const Eigen::MatrixXd>,2>;
const char* ds_in_element = R"igl_Qu8mg5v7(
Determine whether each point in a list of points is in the elements of a mesh.
 
Parameters:
------
V : #V by dim list of mesh vertex positions.
Ele : #Ele by dim+1 list of mesh indices into #V.
Q  : #Q by dim list of query point positions
aabb :  axis-aligned bounding box tree object (see AABB.h)

Returns:
-------
I : #Q list of indices into Ele of first containing element (-1 means no
containing element)
)igl_Qu8mg5v7";
npe_function(in_element_3)
npe_doc(  ds_in_element)
npe_arg(V, Eigen::MatrixXd)
npe_arg(Ele, Eigen::MatrixXi)
npe_arg(Q, Eigen::MatrixXd)
npe_arg(aabb, AABB_f64_3)
npe_begin_code()

  Eigen::VectorXi I;
  Eigen::Map<const Eigen::MatrixXd> V_map(V.data(),V.rows(),V.cols());
  igl::in_element(V_map,Ele,Q,aabb,I);
  return npe::move(I);

npe_end_code()


npe_function(in_element_2)
npe_doc(  ds_in_element)
npe_arg(V, Eigen::MatrixXd)
npe_arg(Ele, Eigen::MatrixXi)
npe_arg(Q, Eigen::MatrixXd)
npe_arg(aabb, AABB_f64_2)
npe_begin_code()

  Eigen::VectorXi I;
  Eigen::Map<const Eigen::MatrixXd> V_map(V.data(),V.rows(),V.cols());
  igl::in_element(V_map,Ele,Q,aabb,I);
  return npe::move(I);

npe_end_code()



