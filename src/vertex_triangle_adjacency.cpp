// TODO: __miss __example

#include <npe.h>
#include <typedefs.h>
#include <igl/vertex_triangle_adjacency.h>

const char* ds_vertex_triangle_adjacency = R"igl_Qu8mg5v7(

vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

Parameters
----------
F  #F by 3 list of triangle indices into some vertex list V
n  number of vertices, #V (e.g., F.maxCoeff()+1)

Returns
-------
VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =
  f, means that face f is the jth face (in no particular order) incident
  on vertex i.
NI  #V+1 list  cumulative sum of vertex-triangle degrees with a
  preceeding zero. "How many faces" have been seen before visiting this
  vertex and its incident faces.


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(vertex_triangle_adjacency)
npe_doc(ds_vertex_triangle_adjacency)

npe_arg(f, dense_int, dense_long)
npe_arg(n, int)


npe_begin_code()

  Eigen::VectorXi vf;
  Eigen::VectorXi ni;
  igl::vertex_triangle_adjacency(f, n, vf, ni);
  return std::make_tuple(npe::move(vf), npe::move(ni));

npe_end_code()



