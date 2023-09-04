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






#include <igl/simplify_polyhedron.h>

const char *ds_simplify_polyhedron = R"igl_Qu8mg5v7(

 Simplify a polyhedron represented as a triangle mesh (OV,OF) by collapsing
   any edge that doesn't contribute to defining surface's pointset. This
   _would_ also make sense for open and non-manifold meshes, but the current
   implementation only works with closed manifold surfaces with well defined
   triangle normals.

Parameters
----------
  OV  #OV by 3 list of input mesh vertex positions
  OF  #OF by 3 list of input mesh triangle indices into OV

Returns
-------
    V  #V by 3 list of output mesh vertex positions
    F  #F by 3 list of input mesh triangle indices into V
    J  #F list of indices into OF of birth parents

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(simplify_polyhedron)
npe_doc(ds_simplify_polyhedron)

npe_arg(ov, dense_float, dense_double)
npe_arg(of, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_3d_tri_mesh(ov, of, "ov", "of");
  Eigen::MatrixXd ov_copy = ov.template cast<double>();
  Eigen::MatrixXi of_copy = of.template cast<int>();
  Eigen::MatrixXd v_copy;
  Eigen::MatrixXi f_copy;
  Eigen::VectorXi j_copy;
  igl::simplify_polyhedron(ov_copy, of_copy, v_copy, f_copy, j_copy);

  EigenDenseLike<npe_Matrix_ov> v = v_copy.template cast < typename npe_Matrix_ov::Scalar >();
  EigenDenseLike<npe_Matrix_of> f = f_copy.template cast<typename npe_Matrix_of::Scalar>();
  Eigen::Matrix<npe_Scalar_of,Eigen::Dynamic,1> j = j_copy.template cast<typename npe_Matrix_of::Scalar>();

  return std::make_tuple(npe::move(v), npe::move(f), npe::move(j));

  npe_end_code()
