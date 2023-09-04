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
#include <igl/iterative_closest_point.h>

const char *ds_iterative_closest_point = R"igl_Qu8mg5v7(

Solve for the rigid transformation that places mesh X onto mesh Y using the
iterative closest point method. In particular, optimize:

min      ∫_X inf ‖x*R+t - y‖² dx
R∈SO(3)      y∈Y
t∈R³

Typically optimization strategies include using Gauss Newton
("point-to-plane" linearization) and stochastic descent (sparse random
sampling each iteration).

Parameters
----------
VX  #VX by 3 list of mesh X vertices
FX  #FX by 3 list of mesh X triangle indices into rows of VX
VY  #VY by 3 list of mesh Y vertices
FY  #FY by 3 list of mesh Y triangle indices into rows of VY
num_samples  number of random samples to use (larger --> more accurate,
  but also more suceptible to sticking to local minimum)

Returns
-------
R  3x3 rotation matrix so that (VX*R+t,FX) ~~ (VY,FY)
t  1x3 translation row vector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(iterative_closest_point)
npe_doc(ds_iterative_closest_point)

npe_arg(vx, dense_float, dense_double)
npe_arg(fx, dense_int32, dense_int64)
npe_arg(vy, npe_matches(vx))
npe_arg(fy, npe_matches(fx))
npe_arg(num_samples, int)
npe_arg(max_iters, int)


npe_begin_code()
  assert_valid_3d_tri_mesh(vx, fx, "vx", "fx");
  assert_valid_3d_tri_mesh(vy, fy, "vy", "fy");

  Eigen::MatrixXd vx_copy = vx.template cast<double>();
  Eigen::MatrixXd vy_copy = vy.template cast<double>();

  Eigen::MatrixXi fx_copy = fx.template cast<int>();
  Eigen::MatrixXi fy_copy = fy.template cast<int>();

  Eigen::Matrix3d r_copy;
  Eigen::RowVector3d t_copy;
  igl::iterative_closest_point(vx_copy, fx_copy, vy_copy, fy_copy, num_samples, max_iters, r_copy, t_copy);

  EigenDense<npe_Scalar_vx> r = r_copy.template cast<npe_Scalar_vx>();
  EigenDense<npe_Scalar_vx> t = t_copy.template cast<npe_Scalar_vx>();

  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()






//TODO requires the abb class

// const char* ds_iterative_closest_point = R"igl_Qu8mg5v7(

// Parameters
// ----------


// Returns
// -------


// See also
// --------


// Notes
// -----
// None

// Examples
// --------

//  Inputs:
//      Ytree  precomputed AABB tree for accelerating closest point queries
//      NY  #FY by 3 list of precomputed unit face normals
// )igl_Qu8mg5v7";

// npe_function(iterative_closest_point)
// npe_doc(ds_iterative_closest_point)

// npe_arg(vx, dense_f32, dense_f64)
// npe_arg(fx, dense_f32, dense_f64)
// npe_arg(vy, dense_f32, dense_f64)
// npe_arg(fy, dense_f32, dense_f64)
// npe_arg(ytree, igl::AABB<DerivedVY, 3> &)
// npe_arg(ny, dense_f32, dense_f64)
// npe_arg(num_samples, int)
// npe_arg(max_iters, int)


// npe_begin_code()

//   EigenDense<npe_Scalar_> r;
//   EigenDense<npe_Scalar_> t;
//   igl::iterative_closest_point(vx, fx, vy, fy, ytree, ny, num_samples, max_iters, r, t);
//   return std::make_tuple(npe::move(r), npe::move(t));

// npe_end_code()


