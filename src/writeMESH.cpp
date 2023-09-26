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
#include <igl/writeMESH.h>

const char* ds_writeMESH = R"igl_Qu8mg5v7(
  /// save a tetrahedral volume mesh to a .mesh file
  ///
  /// @tparam Scalar  type for positions and vectors (will be cast as double)
  /// @tparam Index  type for indices (will be cast to int)
  /// @param[in] mesh_file_name  path of .mesh file
  /// @param[in] V  double matrix of vertex positions  #V by 3
  /// @param[in] T  #T list of tet indices into vertex positions
  /// @param[in] F  #F list of face indices into vertex positions
  /// @return true on success, false on errors
  ///
  /// \bug Holes and regions are not supported
)igl_Qu8mg5v7";

npe_function(writeMESH)
npe_doc(ds_writeMESH)
npe_arg(filename, std::string)
npe_arg(V, dense_double, dense_float)
npe_arg(T, dense_int32, dense_int64)
npe_default_arg(F, npe_matches(T), pybind11::array())

npe_begin_code()

  assert_valid_tet_or_tri_mesh(V,T);
  return igl::writeMESH(filename, V, T, F);

npe_end_code()





