//TODO: libigl is not templated...
#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/comiso/nrosy.h>

const char* ds_nrosy = R"igl_Qu8mg5v7(
Generate a N-RoSy field from a sparse set of constraints.

Parameters
----------
v : #v by 3 array of mesh vertex coordinates
f : #f by 3 array of mesh faces (must be triangles)
b : #b by 1 array of constrained face indices
bc : #b by 3 array of representative vectors for the constrained faces
b_soft : #s by 1 b for soft constraints
w_soft : #s by 1 weight for the soft constraints (0-1)
bc_soft : #s by 3 bc for soft constraints
n : the degree of the N-RoSy vector field
soft : the strength of the soft constraints w.r.t. smoothness (0 -> smoothness only, 1->constraints only)

Returns
-------
r : #f by 3 the representative vectors of the interpolated field
S : #v by 1 the singularity index for each vertex (0 = regular)

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(nrosy)
npe_doc(ds_nrosy)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(b, npe_matches(f))
npe_arg(bc, npe_matches(v))
npe_arg(b_soft, npe_matches(f))
npe_arg(w_soft, npe_matches(v))
npe_arg(bc_soft, npe_matches(v))
npe_arg(n, int)
npe_arg(soft, double)


npe_begin_code()
  EigenDenseLike<npe_Matrix_v> r;
  EigenDenseLike<npe_Matrix_v> s;
  igl::copyleft::comiso::nrosy(v, f, b, bc, b_soft, w_soft, bc_soft, n, soft, r, s);
  return std::make_tuple(npe::move(r), npe::move(s));

npe_end_code()

