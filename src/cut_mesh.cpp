#include <igl/cut_mesh.h>
#include <npe.h>

const char* ds_cut_mesh = R"igl_Qu8mg5v7(
Compute the barycenter of every simplex

Parameters
----------
v : #v x dim matrix of vertex coordinates
f : #f x simplex_size  matrix of indices of simplex corners into V
cuts :

Returns
-------

See also
--------

Notes
-----

Examples
--------


)igl_Qu8mg5v7";

npe_function(cut_mesh)
npe_doc(ds_cut_mesh)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(cuts, dense_int)
npe_begin_code()

    // FIXME: Copying is bad m'kay but libIGL's templates are broken
    npe_Matrix_v Vcopy = v;
    npe_Matrix_f Fcopy = f;
    npe_Matrix_cuts cutsCopy = cuts;

    npe_Matrix_v Vcut;
    npe_Matrix_f Fcut;

    igl::cut_mesh(Vcopy, Fcopy, cutsCopy, Vcut, Fcut);

    return std::make_tuple(npe::move(Vcut), npe::move(Fcut));

npe_end_code()
