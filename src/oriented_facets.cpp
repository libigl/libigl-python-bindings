#include <npe.h>
#include <typedefs.h>
#include <igl/oriented_facets.h>

const char* ds_oriented_facets = R"igl_Qu8mg5v7(
Determines all 'directed [facets](https:en.wikipedia.org/wiki/Simplex#Elements)' of a given set
of simplicial elements. For a manifold triangle mesh, this computes all half-edges.
For a manifold tetrahedral mesh, this computes all half-faces.

Parameters
----------
f : #F by simplex_size list of simplices


Returns
-------
#E : by simplex_size-1 list of half-edges/facets

See also
--------
edges

Notes
-----
This is not the same as igl::edges because this includes every
directed edge including repeats (meaning interior edges on a surface will
show up once for each direction and non-manifold edges may appear more than
once for each direction).

Examples
--------

)igl_Qu8mg5v7";

npe_function(oriented_facets)
npe_doc(ds_oriented_facets)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  npe_Matrix_f e;
  igl::oriented_facets(f, e);
  return npe::move(e);

npe_end_code()


