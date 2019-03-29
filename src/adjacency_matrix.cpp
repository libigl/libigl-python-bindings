#include <npe.h>
#include <typedefs.h>
#include <igl/adjacency_matrix.h>

const char* ds_adjacency_matrix = R"igl_Qu8mg5v7(
Constructs the graph adjacency matrix of a given mesh (v, f).

Parameters
----------
f : #f by dim list of mesh simplices

Returns
-------
a : max(f) by max(f) cotangent matrix, each row i corresponding to v(i, :)

See also
--------
adjacency_list, edges, cotmatrix, diag

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> a = adjacency_matrix(f)

# Sum each row 
>>> a_sum = np.sum(a, axis=1)

# Convert row sums into diagonal of sparse matrix
>>> a_diag = diag(a_sum)

# Build uniform laplacian
>>> u = a - a_diag
)igl_Qu8mg5v7";

npe_function(adjacency_matrix)
npe_doc(ds_adjacency_matrix)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  EigenSparseLike<npe_Matrix_f> a;
  igl::adjacency_matrix(f, a);
  return npe::move(a);

npe_end_code()


