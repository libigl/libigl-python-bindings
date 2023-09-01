// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 KarlLeell
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/cylinder.h>

const char* ds_cylinder = R"igl_Qu8mg5v7(

Construct a triangle mesh of a cylinder (without caps)

Parameters
----------
axis_devisions  number of vertices _around the cylinder_
height_devisions  number of vertices _up the cylinder_

Returns
-------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of triangle indices into V

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(cylinder)
npe_doc(ds_cylinder)

npe_arg(axis_devisions, int)
npe_arg(height_devisions, int)


npe_begin_code()

  Eigen::MatrixXd v;
  Eigen::MatrixXi f;
  igl::cylinder(axis_devisions, height_devisions, v, f);
  EigenDenseFloat v_row_major = v;
  EigenDenseInt f_row_major = f.template cast<typename EigenDenseInt::Scalar>();
  return std::make_tuple(npe::move(v_row_major), npe::move(f_row_major));

npe_end_code()


