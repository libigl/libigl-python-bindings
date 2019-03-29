#include <npe.h>
#include <typedefs.h>
#include <igl/edges.h>

const char* ds_edges = R"igl_Qu8mg5v7(
Constructs a list of unique edges represented in a given mesh (v, f)

Parameters
----------
f : #F by dim list of mesh faces (must be triangles or tets)

Returns
-------
#e by 2 list of edges in no particular order

See also
--------
adjacency_matrix

Notes
-----

Examples
--------
>>> V, F, _ = igl.readOFF("test.off)
>>> E = igl.edges(F)

)igl_Qu8mg5v7";

npe_function(edges)
npe_doc(ds_edges)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  npe_Matrix_f e;
  igl::edges(f, e);
  return npe::move(e);

npe_end_code()
