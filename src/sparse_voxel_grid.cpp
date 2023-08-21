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

#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <igl/sparse_voxel_grid.h>

const char *ds_sparse_voxel_grid = R"igl_Qu8mg5v7(

Given a point, p0, on an isosurface, construct a shell of epsilon sized cubes surrounding the surface.
These cubes can be used as the input to marching cubes.


Parameters
----------
p0  A 3D point on the isosurface surface defined by scalarFunc(x) = 0
scalarFunc  A scalar function from R^3 to R -- points which map to 0 lie
            on the surface, points which are negative lie inside the surface,
            and points which are positive lie outside the surface
eps  The edge length of the cubes surrounding the surface
expected_number_of_cubes  This pre-allocates internal data structures to speed things up

Returns
-------

CS  #cube-vertices by 1 list of scalar values at the cube vertices
CV  #cube-vertices by 3 list of cube vertex positions
CI  #number of cubes by 8 list of indexes into CS and CV. Each row represents a cube

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(sparse_voxel_grid)
npe_doc(ds_sparse_voxel_grid)

npe_arg(p0, EigenDenseFloat)
npe_arg(scalar_func, const std::function< typename EigenDenseFloat::Scalar (Eigen::Matrix<typename EigenDenseFloat::Scalar, 1, 3> &) >)
npe_arg(eps, double)
npe_arg(expected_number_of_cubes, int)


npe_begin_code()
  assert_size_equals(p0, 3, "p0");

  EigenDenseFloat cs;
  EigenDenseFloat cv;
  EigenDenseInt ci;
  Eigen::Matrix<typename EigenDenseFloat::Scalar, 1, 3> p0_copy;
  if(p0.cols() == 1)
    p0_copy = p0.transpose();
  else
    p0_copy = p0;

  igl::sparse_voxel_grid(p0_copy, scalar_func, eps, expected_number_of_cubes, cs, cv, ci);
  return std::make_tuple(npe::move(cs), npe::move(cv), npe::move(ci));

npe_end_code()


