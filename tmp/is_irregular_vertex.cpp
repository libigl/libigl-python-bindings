#include <npe.h>
#include <typedefs.h>
#include <igl/is_irregular_vertex.h>
#include <pybind11/stl.h>

const char* ds_is_irregular_vertex = R"igl_Qu8mg5v7(
Determine if a vertex is irregular, i.e. it has more than 6 (triangles) or 4 (quads) incident edges. Vertices on the boundary are ignored.

Parameters
----------
v : #v by dim array of vertex positions
f : #f by 3[4] array of triangle[quads] indices

Returns
-------
s : #v list of bools revealing whether vertices are singular

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(is_irregular_vertex)
npe_doc(ds_is_irregular_vertex)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)

npe_begin_code()
  return igl::is_irregular_vertex(v, f);

npe_end_code()


