// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>
// On macos with cp36, termios.h is getting included for some reason and it
// defines B0
#ifdef B0
#  undef B0
#endif
#include <igl/fit_cubic_bezier.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>


const char *ds_fit_cubic_bezier = R"igl_Qu8mg5v7(
Fit a cubic bezier spline (G1 continuous) to an ordered list of input
points in any dimension, according to "An algorithm for automatically
fitting digitized curves" [Schneider 1990].

Parameters
----------
  d  #d by dim list of points along a curve to be fit with a cubic bezier
    spline (should probably be roughly uniformly spaced). If d(0)==d(end),
    then will treat as a closed curve.
  error  maximum squared distance allowed
Returns
-------
  cubics #cubics list of 4 by dim lists of cubic control points

)igl_Qu8mg5v7";

npe_function(fit_cubic_bezier)
npe_doc(ds_fit_cubic_bezier)

npe_arg(d, dense_float, dense_double)
npe_arg(error, double)

npe_begin_code()
  // igl::fit_cubic_bezier is hard-coded to double, so for now copy.
  Eigen::MatrixXd d_cpy = d.template cast<double>();
  std::vector<Eigen::MatrixXd> c_cpy;
  igl::fit_cubic_bezier(d_cpy,error,c_cpy);
  std::vector<EigenDenseLike<npe_Matrix_d>> c(c_cpy.size());
  std::transform (c_cpy.begin(), c_cpy.end(), c.begin(),
      [](const Eigen::MatrixXd & ci){ return ci.cast<npe_Scalar_d>();});
  // numpyeigen's pybind11 fork `numpy_hacks_stable` is printing "Encapsulate move!"
  // https://github.com/fwilliams/numpyeigen/issues/58
  return pybind11::detail::type_caster<decltype(c)>::cast(c, pybind11::return_value_policy::move, pybind11::none());

npe_end_code()

