#include <npe.h>
#include <typedefs.h>
#include <igl/is_vertex_manifold.h>

const char* ds_is_vertex_manifold = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Check if a mesh is vertex-manifold. This only checks whether the faces
   incident on each vertex form exactly one connected component. Vertices
   incident on non-manifold edges are not consider non-manifold by this
   function (see is_edge_manifold.h). Unreferenced verties are considered
   non-manifold (zero components).
  
   Inputs:
     F  #F by 3 list of triangle indices
   Outputs:
     B  #V list indicate whether each vertex is locally manifold.
   Returns whether mesh is vertex manifold.
  
   See also: is_edge_manifold
)igl_Qu8mg5v7";

npe_function(is_vertex_manifold)
npe_doc(ds_is_vertex_manifold)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> b;
  igl::is_vertex_manifold(f, b);
  return npe::move(b);

npe_end_code()


