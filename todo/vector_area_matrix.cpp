#include <npe.h>
#include <typedefs.h>
#include <igl/vector_area_matrix.h>

const char* ds_vector_area_matrix = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Constructs the symmetric area matrix A, s.t.  [V.col(0)' V.col(1)'] * A *
   [V.col(0); V.col(1)] is the **vector area** of the mesh (V,F).
  
   Templates:
     DerivedV  derived type of eigen matrix for V (e.g. derived from
       MatrixXd)
     DerivedF  derived type of eigen matrix for F (e.g. derived from
       MatrixXi)
     Scalar  scalar type for eigen sparse matrix (e.g. double)
   Inputs:
     F  #F by 3 list of mesh faces (must be triangles)
   Outputs:
     A  #Vx2 by #Vx2 area matrix
  
)igl_Qu8mg5v7";

npe_function(vector_area_matrix)
npe_doc(ds_vector_area_matrix)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Sparse_f64 a;
  igl::vector_area_matrix(f, a);
  return npe::move(a);

npe_end_code()


