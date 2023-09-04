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
#include <pybind11/functional.h>
#include <pybind11/stl.h>






#include <igl/flip_avoiding_line_search.h>

const char* ds_flip_avoiding_line_search = R"igl_Qu8mg5v7(

A bisection line search for a mesh based energy that avoids triangle flips as suggested in
"Bijective Parameterization with Free Boundaries" (Smith J. and Schaefer S., 2015).

The user specifies an initial vertices position (that has no flips) and target one (that my have flipped triangles).
This method first computes the largest step in direction of the destination vertices that does not incur flips, and then minimizes a given energy using this maximal step and a bisection linesearch (see igl::line_search).

Supports both triangle and tet meshes.

Parameters
----------
F         #F by 3/4 list of mesh faces or tets
cur_v     #V by dim list of variables
dst_v  	  #V by dim list of target vertices. This mesh may have flipped triangles
energy    A function to compute the mesh-based energy (return an energy that is bigger than 0)
cur_energy(OPTIONAL)         The energy at the given point. Helps save redundant c  omputations. This is optional. If not specified, the function will compute it.


Returns
-------
cur_v  	  #V by dim list of variables at the new location
Returns the energy at the new point


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(flip_avoiding_line_search)
npe_doc(ds_flip_avoiding_line_search)

npe_arg(f, dense_int32, dense_int64)
npe_arg(cur_v, dense_float, dense_double)
npe_arg(dst_v, npe_matches(cur_v))
npe_arg(energy, std::function<double(Eigen::MatrixXd&)>)
npe_arg(cur_energy, double)

npe_begin_code()
  assert_shapes_match(cur_v, dst_v, "cur_v", "dst_v");
  assert_valid_tet_or_tri_mesh_faces(f);
  if(f.cols() == 3)
  {
    assert_cols_equals(cur_v, 2, "cur_v");
    assert_cols_equals(dst_v, 2, "dst_v");
  }
  else
  {
    assert_cols_equals(cur_v, 3, "cur_v");
    assert_cols_equals(dst_v, 3, "dst_v");
  }

  //TODO: remove __copy
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd cur_v_copy = cur_v.template cast<double>();
  Eigen::MatrixXd dst_v_copy = dst_v.template cast<double>();
  double ret_energy = igl::flip_avoiding_line_search(f_copy, cur_v_copy, dst_v_copy, energy, cur_energy);
  EigenDenseFloat cur_v_row_major = cur_v_copy;
  return std::make_tuple(ret_energy, npe::move(cur_v_row_major));

npe_end_code()
