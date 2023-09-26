// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/writeMSH.h>

const char* ds_writeMSH = R"igl_Qu8mg5v7(
  /// write triangle surface mesh and tetrahedral volume mesh to .msh file
  ///
  /// @param[in] msh - file name
  /// @param[in] X  eigen double matrix of vertex positions  #X by 3
  /// @param[in] Tri  #Tri eigen integer matrix of triangular faces indices into vertex positions
  /// @param[in] Tet  #Tet eigen integer matrix of tetrahedral indices into vertex positions
  /// @param[in] TriTag #Tri eigen integer vector of tags associated with surface faces
  /// @param[in] TetTag #Tet eigen integer vector of tags associated with volume elements
  /// @param[in] XFields #XFields list of strings with field names associated with nodes
  /// @param[in] XF      #XFields list of eigen double matrices, fields associated with nodes 
  /// @param[in] EFields #EFields list of strings with field names associated with elements
  /// @param[in] TriF    #EFields list of eigen double matrices, fields associated with surface elements
  /// @param[in] TetF    #EFields list of eigen double matrices, fields associated with volume elements
  ///
  /// \bug files are always stored in binary format
  /// \bug file format is 2.2
  /// \bug only triangle surface elements and tetrahedral volumetric elements are supported
  /// \bug only 3D information is supported
  /// \bug the tag id is duplicated for physical (0) and elementary (1)
  /// \bug same element fields are expected to be associated with surface elements and volumetric elements
)igl_Qu8mg5v7";

npe_function(writeMSH)
npe_doc(ds_writeMSH)
npe_arg(filename, std::string)
// float not allowed because writeMSH is not templated
npe_arg(X, dense_double)
npe_arg(Tri, dense_int32, dense_int64)
npe_default_arg(Tet, npe_matches(Tri), pybind11::array())
npe_default_arg(TriTag, npe_matches(Tri), pybind11::array())
npe_default_arg(TetTag, npe_matches(Tri), pybind11::array())

npe_begin_code()

std::vector<std::string> XFields, EFields;
std::vector<Eigen::MatrixXd> XF, TriF, TetF;
Eigen::MatrixXd X_copy = X.template cast<double>();
Eigen::MatrixXi Tri_copy = Tri.template cast<int>();
Eigen::MatrixXi Tet_copy = Tet.template cast<int>();
Eigen::MatrixXi TriTag_copy = TriTag.template cast<int>();
Eigen::MatrixXi TetTag_copy = TetTag.template cast<int>();

return igl::writeMSH(
  filename, 
  X_copy, 
  Tri_copy,
  Tet_copy,
  TriTag_copy,
  TetTag_copy,
  XFields,
  XF,
  EFields,
  TriF,
  TetF);

npe_end_code()





