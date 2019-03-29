#include <npe.h>
#include <typedefs.h>
#include <igl/orientable_patches.h>

const char* ds_orientable_patches = R"igl_Qu8mg5v7(
Compute connected components of facets connected by manifold edges.

Parameters
----------
f : n by dim array of face ids

Returns
-------
A tuple (c, A) where c is an array of component ids (starting with 0)
and A is a #f x #f adjacency matri

See also
--------
components

Notes
-----
Known bugs: This will detect a moebius strip as a single patch (manifold, non-orientable) and also non-manfiold, yet orientable patches.

Examples
--------

)igl_Qu8mg5v7";

npe_function(orientable_patches)
npe_doc(ds_orientable_patches)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

    npe_Matrix_f c;
    EigenSparseLike<npe_Matrix_f> A;
    igl::orientable_patches(f, c, A);
    return std::make_tuple(npe::move(c), npe::move(A));

npe_end_code()

