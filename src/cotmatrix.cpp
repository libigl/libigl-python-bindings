#include <npe.h>
#include <typedefs.h>
#include <igl/cotmatrix.h>

const char* ds_cotmatrix = R"igl_Qu8mg5v7(
Constructs the cotangent stiffness matrix (discrete laplacian) for a given mesh
(v, f).

Parameters
----------
v : #v by dim list of mesh vertex positions
f : #f by simplex_size list of mesh faces (must be triangles)

Returns
-------
l : #v by #v cotangent matrix, each row i corresponding to v(i, :)

See also
--------
adjacency_matrix

Notes
-----
This Laplacian uses the convention that diagonal entries are
**minus** the sum of off-diagonal entries. The diagonal entries are
therefore in general negative and the matrix is **negative** semi-definite
(immediately, -L is **positive** semi-definite)

Examples
--------
# Mesh in (v, f)
>>> l = cotmatrix(v, f)
)igl_Qu8mg5v7";

npe_function(cotmatrix)
npe_doc(ds_cotmatrix)
npe_arg(v, dense_f64, dense_f32)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  EigenSparseLike<npe_Matrix_v> l;
  igl::cotmatrix(v, f, l);
  return npe::move(l);

npe_end_code()


