#include <npe.h>
#include <typedefs.h>
#include <igl/vector_area_matrix.h>

const char* ds_vector_area_matrix = R"igl_Qu8mg5v7(
Constructs the symmetric area matrix A, s.t. [V.col(0)' V.col(1)'] * A *
   [V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).
Parameters
----------
f : #f by 3 array of mesh faces (must be triangles)

Returns
-------
a : #vx2 by #vx2 area matrix

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(vector_area_matrix)
npe_doc(ds_vector_area_matrix)
npe_arg(f, dense_int, dense_longlong)
npe_begin_code()

  EigenSparseLike<npe_Matrix_f> a;
  igl::vector_area_matrix(f, a);
  return npe::move(a);

npe_end_code()


