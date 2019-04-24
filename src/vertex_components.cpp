#include <npe.h>
#include <typedefs.h>
#include <igl/vertex_components.h>

const char* ds_vertex_components = R"igl_Qu8mg5v7(
Compute connected components of the vertices of a mesh given the mesh' face indices.

Parameters
----------
f : #f x dim array of face indices

Returns
-------
An array of component ids (starting with 0)

See also
--------
vertex_components_from_adjacency_matrix
face_components_from_faces

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(vertex_components)
npe_doc(ds_vertex_components)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()
    npe_Matrix_f c;
    igl::vertex_components(f, c);
    return npe::move(c);
npe_end_code()


const char* ds_vertex_components_from_adjacency_matrix = R"igl_Qu8mg5v7(
Compute connected components of a graph represented by a sparse adjacency
matrix.

Parameters
----------
a : n by n sparse adjacency matrix

Returns
-------
A tuple (c, counts) where c is an array of component ids (starting with 0)
and counts is a #components array of counts for each component

See also
--------
vertex_components
face_components

Notes
-----

Examples
--------
  
)igl_Qu8mg5v7";

npe_function(vertex_components_from_adjacency_matrix)
npe_doc(ds_vertex_components_from_adjacency_matrix)
npe_arg(a, sparse_i32, sparse_i64)
npe_begin_code()
    EigenDense<npe_Scalar_a> c;
    EigenDense<npe_Scalar_a> counts;
    igl::vertex_components(a, c, counts);
    return std::make_tuple(npe::move(c), npe::move(counts));
npe_end_code()



