// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <pybind11/functional.h>
#include <typedefs.h>
#include <pybind11/stl.h>
#include <igl/pso.h>

const char *ds_pso = R"igl_Qu8mg5v7ss(
Solve the problem:

  minimize f(x)
  subject to lb ≤ x ≤ ub

by particle swarm optimization (PSO).


Parameters
----------
f  function that evaluates the objective for a given "particle" location
LB  #X vector of lower bounds
UB  #X vector of upper bounds
max_iters  maximum number of iterations
population  number of particles in swarm

Returns
-------
f(X) objective corresponding to best particle seen so far
X  best particle seen so far


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7ss";

npe_function(pso)
npe_doc(ds_pso)

npe_arg(f, const std::function< typename EigenDenseFloat::Scalar (Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> &) >)
npe_arg(lb, EigenDenseFloat)
npe_arg(ub, EigenDenseFloat)
npe_arg(max_iters, int)
npe_arg(population, int)


npe_begin_code()
  Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> x_copy;
  const auto obj = igl::pso(f, lb, ub, max_iters, population, x_copy);
  EigenDenseFloat x = x_copy;
  return std::make_tuple(obj, npe::move(x));

npe_end_code()



// const char *ds_psop = R"igl_Qu8mg5v7ssp(
// Solve the problem:
//
//   minimize f(x)
//   subject to lb ≤ x ≤ ub
//
// by particle swarm optimization (PSO).
//
//
// Parameters
// ----------
// f  function that evaluates the objective for a given "particle" location
// LB  #X vector of lower bounds
// UB  #X vector of upper bounds
// P  whether each DOF is periodic
// max_iters  maximum number of iterations
// population  number of particles in swarm
//
// Returns
// -------
// X  best particle seen so far
// Returns objective corresponding to best particle seen so far
//
// See also
// --------
//
//
// Notes
// -----
// None
//
// Examples
// --------
//
// )igl_Qu8mg5v7ssp";

// npe_function(pso_periodic)
// npe_doc(ds_psop)
//
// npe_arg(f, const std::function< typename EigenDenseFloat::Scalar (Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> &) >)
// npe_arg(lb, EigenDenseFloat)
// npe_arg(ub, EigenDenseFloat)
// npe_arg(p, EigenDenseFloat) //SHOULD BE BOOLEAN, BUT IS NOT USED ANYWAYS
// npe_arg(max_iters, int)
// npe_arg(population, int)
//
//
// npe_begin_code()
//   Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> x_copy;
//   const auto obj = igl::pso(f, lb, ub, p, max_iters, population, x_copy);
//   EigenDenseFloat x = x_copy;
//   return std::make_tuple(obj, npe::move(x));
//
// npe_end_code()
