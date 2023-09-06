// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example
// TODO: remove __copy
// copy is necessary since the winding number only supports matrices
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/winding_number.h>

const char *ds_winding_number = R"igl_Qu8mg5v7(
 WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron
   described by points (vectors) V
Parameters
----------
    V  n by 3 list of vertex positions
    F  #F by 3 list of triangle indices, minimum index is 0
    O  no by 3 list of origin positions

Returns
-------
    S  no by 1 list of winding numbers

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(winding_number)
npe_doc(ds_winding_number)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(o, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_cols_match(v, o, "v", "o");
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd o_copy = o.template cast<double>();

  Eigen::MatrixXd w;
  igl::winding_number(v_copy, f_copy, o_copy, w);
  return npe::move(w);

npe_end_code()




const char* ds_winding_number1 = R"igl_Qu8mg5v7(
 Compute winding number of a single point

Parameters
----------
    V  n by dim list of vertex positions
    F  #F by dim list of triangle indices, minimum index is 0
    p  single origin position

Returns
-------
  w  winding number of this point

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(winding_number_for_point)
npe_doc(ds_winding_number1)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(p, dense_float, dense_double)


npe_begin_code()
  assert_valid_tet_or_tri_mesh(v, f);
  assert_cols_match(v, f, "v", "f");
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd p_copy = p.template cast<double>();
  return igl::winding_number(v_copy, f_copy, p_copy);

npe_end_code()


