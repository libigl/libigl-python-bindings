//TODO: Wierd error
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
npe_arg(f, dense_int, dense_longlong)
npe_arg(s, dense_float, dense_double)
npe_begin_code()

  npe_Matrix_s sf;
  igl::average_onto_faces(f, s, sf);
  return npe::move(sf);

npe_end_code()


