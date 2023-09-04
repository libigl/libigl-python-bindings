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
#include <igl/false_barycentric_subdivision.h>

const char *ds_false_barycentric_subdivision = R"igl_Qu8mg5v7(

 Refine the mesh by adding the barycenter of each face

Parameters
----------
  V       #V by 3 coordinates of the vertices
  F       #F by 3 list of mesh faces (must be triangles)

Returns
-------
  VD      #V + #F by 3 coordinate of the vertices of the dual mesh
             The added vertices are added at the end of VD (should not be
             same references as (V,F)
  FD      #F*3 by 3 faces of the dual mesh

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(false_barycentric_subdivision)
npe_doc(ds_false_barycentric_subdivision)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  //TODO: only 2 templates in igl...

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();

  Eigen::MatrixXd vd_copy;
  Eigen::MatrixXi fd_copy;

  igl::false_barycentric_subdivision(v_copy, f_copy, vd_copy, fd_copy);

  EigenDenseLike<npe_Matrix_v> vd = vd_copy.template cast<typename npe_Matrix_v::Scalar>();
  EigenDenseLike<npe_Matrix_f> fd = fd_copy.template cast<typename npe_Matrix_f::Scalar>();
  return std::make_tuple(npe::move(vd), npe::move(fd));

npe_end_code()


