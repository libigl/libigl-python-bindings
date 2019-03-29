#include <npe.h>
#include <typedefs.h>
#include <igl/average_onto_vertices.h>

const char* ds_average_onto_vertices = R"igl_Qu8mg5v7(
Move a scalar field defined on faces to vertices by averaging

Parameters
----------
v : #v by vdim array of mesh vertices
f : #f by simplex_count array of simplex indices
s : #f by dim scalar field defined on simplices

Returns
-------
#v by dim scalar field defined on vertices

See also
--------
average_onto_faces

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(average_onto_vertices)
npe_doc(ds_average_onto_vertices)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(s, dense_f32, dense_f64) // TODO: Maybe do a matches here
npe_begin_code()

  npe_Matrix_s sv;
  igl::average_onto_vertices(v, f, s, sv);
  return npe::move(sv);

npe_end_code()


