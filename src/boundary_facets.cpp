#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/boundary_facets.h>

const char* ds_boundary_facets = R"igl_Qu8mg5v7(
Determine boundary faces (edges) of tetrahedra (triangles).

Parameters
----------
t : tetrahedron or triangle index list, m by 4/3, where m is the number of tetrahedra/triangles

Returns
-------
f : list of boundary faces, n by 3/2, where n is the number of boundary faces/edges

See also
--------
None

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> b = boundary_facets(f)
)igl_Qu8mg5v7";

npe_function(boundary_facets)
npe_doc(ds_boundary_facets)
npe_arg(t, dense_int, dense_longlong)
npe_begin_code()

  EigenDense<npe_Scalar_t> f;
  igl::boundary_facets(t, f);
  return npe::move(f);

npe_end_code()

