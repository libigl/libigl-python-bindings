#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/facet_components.h>

const char* ds_face_components = R"igl_Qu8mg5v7(
Compute connected components of facets based on edge-edge adjacency,

Parameters
----------
f : #f x 3 array of triangle indices

Returns
-------
An array, c, with shape (#f,), of component ids

See also
--------
vertex_components
vertex_components_from_adjacency_matrix

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(face_components)
npe_doc(ds_face_components)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_begin_code()
    assert_valid_tri_mesh_faces(f);
    npe_Matrix_f c;
    igl::facet_components(f, c);
    return npe::move(c);
npe_end_code()
