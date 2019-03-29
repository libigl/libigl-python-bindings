#include <npe.h>
#include <typedefs.h>
#include <igl/barycentric_coordinates.h>
#include <iostream>
const char* ds_barycentric_coordinates_tet = R"igl_Qu8mg5v7(

Compute barycentric coordinates in a tet corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, `c` and `d` are the vertices of each tet. I.e. one tet is
`a[i, :], b[i, :], c[i, :], d[:, i]`.

Parameters
----------
p : #P by 3 Query points in 3d
a : #P by 3 Tet corners in 3d
b : #P by 3 Tet corners in 3d
c : #P by 3 Tet corners in 3d
d : #P by 3 Tet corners in 3d

Returns
-------
#P by 4 list of barycentric coordinates

See also
--------

Notes
-----

Examples
--------
     
)igl_Qu8mg5v7";

npe_function(barycentric_coordinates_tet)
npe_doc(ds_barycentric_coordinates_tet)
npe_arg(p, dense_f32, dense_f64)
npe_arg(a, npe_matches(p))
npe_arg(b, npe_matches(p))
npe_arg(c, npe_matches(p))
npe_arg(d, npe_matches(p))
npe_begin_code()

    npe_Matrix_p l;
    igl::barycentric_coordinates(p, a, b, c, d, l);
    return npe::move(l);

npe_end_code()





const char* ds_barycentric_coordinates_tri = R"igl_Qu8mg5v7(

Compute barycentric coordinates in a triangle corresponding to the Euclidean coordinates in `p`.
The input arrays `a`, `b`, and `c` are the vertices of each triangle. I.e. one triangle is
`a[i, :], b[i, :], c[i, :]`.

Parameters
----------
p : #P by 3 Query points in 3d
a : #P by 3 Tri corners in 3d
b : #P by 3 Tri corners in 3d
c : #P by 3 Tri corners in 3d

Returns
-------
#P by 3 list of barycentric coordinates

See also
--------

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(barycentric_coordinates_tri)
npe_doc(ds_barycentric_coordinates_tri)
npe_arg(p, dense_f32, dense_f64)
npe_arg(a, npe_matches(p))
npe_arg(b, npe_matches(p))
npe_arg(c, npe_matches(p))
npe_begin_code()

    npe_Matrix_p l;
    igl::barycentric_coordinates(p, a, b, c, l);
    return npe::move(l);

npe_end_code()
