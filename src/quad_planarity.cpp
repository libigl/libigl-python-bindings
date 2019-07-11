// TODO: missing __example

#include <npe.h>
#include <typedefs.h>
#include <igl/quad_planarity.h>

const char* ds_quad_planarity = R"igl_Qu8mg5v7(
Compute planarity of the faces of a quad mesh.

Parameters
----------
v : #v by 3 array of mesh vertex 3D positions
f : #f by 4 array of face (quad) indices

Returns
-------
p : #f by 1 array of mesh face (quad) planarities

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(quad_planarity)
npe_doc(ds_quad_planarity)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_begin_code()

  npe_Matrix_v p;
  igl::quad_planarity(v, f, p);
  return npe::move(p);

npe_end_code()


