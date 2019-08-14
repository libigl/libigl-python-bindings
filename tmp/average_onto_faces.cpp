//TODO: Wierd error
/*
ImportError: dlopen(/Users/teseo/data/igl/python/igl/pyigl.cpython-36m-darwin.so, 2): Symbol not found: __ZN3igl18average_onto_facesIN5Eigen3MapINS1_6MatrixIiLin1ELin1ELi0ELin1ELin1EEELi16ENS1_6StrideILi0ELi0EEEEENS2_INS3_IdLin1ELin1ELi0ELin1ELin1EEELi16ES6_EES8_EEvRKNS1_10MatrixBaseIT_EERKNSA_IT0_EERNS1_15PlainObjectBaseIT1_EE
  Referenced from: /Users/teseo/data/igl/python/igl/pyigl.cpython-36m-darwin.so
  */
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/average_onto_faces.h>

const char* ds_average_onto_faces = R"igl_Qu8mg5v7(
Move a scalar field defined on vertices to faces by averaging

Parameters
----------
f : #f by ss list of simplexes/faces
s : #v by dim list of per-vertex values

Returns
-------
#f by dim list of per-face values

See also
--------
average_onto_vertices

Notes
-----

Examples
--------
)igl_Qu8mg5v7";

npe_function(average_onto_faces)
npe_doc(ds_average_onto_faces)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(s, dense_float, dense_double)
npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f);

  npe_Matrix_s sf;
  igl::average_onto_faces(f, s, sf);
  return npe::move(sf);

npe_end_code()
