#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/boundary_loop.h>

const char* ds_boundary_loop = R"igl_Qu8mg5v7(
Compute ordered boundary loops for a manifold mesh and return the longest loop in terms of vertices.

Parameters
----------
f : #v by dim array of mesh faces

Returns
-------
l : ordered list of boundary vertices of longest boundary loop

See also
--------


Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>>l = boundary_loop(f)
)igl_Qu8mg5v7";

npe_function(boundary_loop)
npe_doc(ds_boundary_loop)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  EigenDenseLike<npe_Matrix_f> l;
  igl::boundary_loop(f, l);
  return npe::move(l);

npe_end_code()

