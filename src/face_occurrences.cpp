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




#include <igl/face_occurrences.h>

const char *ds_face_occurrences = R"igl_Qu8mg5v7(
 Count the occruances of each face (row) in a list of face indices (irrespecitive of order)
Parameters
----------
  F  #F by simplex-size

Returns
-------
  C  #F list of counts

See also
--------


Notes
-----
  Known bug: triangles/tets only (where ignoring order still gives simplex)

Examples
--------

)igl_Qu8mg5v7";

npe_function(face_occurrences)
npe_doc(ds_face_occurrences)

npe_arg(f, dense_int32, dense_int64)


npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f);

  EigenDenseLike<npe_Matrix_f> c;
  igl::face_occurrences(f, c);
  return npe::move(c);

npe_end_code()


