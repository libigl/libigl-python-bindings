// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>
#include <igl/readMSH.h>

const char *ds_read_msh = R"igl_Qu8mg5v7(
Read a mesh (e.g., tet mesh) from a gmsh .msh file

Parameters
----------
filename  path to .msh file
dtype : data-type of the returned vertices, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------

V  #V by 3 list of 3D mesh vertex positions
T  #T by ss list of 3D ss-element indices into V (e.g., ss=4 for tets)

See also
--------

Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(read_msh)
npe_doc(ds_read_msh)

npe_arg(filename, std::string)
npe_default_arg(dtypef, npe::dtype, "float")

npe_begin_code()
  Eigen::MatrixXd v;
  Eigen::MatrixXi t;

  //NOTE: readMSH only support vertices as matrix of doubles. We instead cast the output accordingly.
  bool ret = igl::readMSH(filename, v, t);
  if (!ret) {
    throw std::invalid_argument("File '" + filename + "' not found.");
  }
  
  EigenDenseInt t_row_maj = t.template cast<typename EigenDenseInt::Scalar>();

  if (dtypef.type() == npe::type_f32) {
    EigenDenseF32 v_row_maj = v.template cast <typename EigenDenseF32::Scalar>();
    return std::make_tuple(npe::move(v_row_maj ), npe::move(t_row_maj));
  } else if (dtypef.type() == npe::type_f64) {
    EigenDenseF64 v_row_maj = v.template cast <typename EigenDenseF64::Scalar>();
    return std::make_tuple(npe::move(v_row_maj ), npe::move(t_row_maj));
  }
  
  throw pybind11::type_error("Only float32 and float64 dtypes are supported.");

npe_end_code()


