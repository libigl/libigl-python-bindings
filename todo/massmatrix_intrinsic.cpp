#include <npe.h>
#include <typedefs.h>






#include <igl/massmatrix_intrinsic.h>

const char* ds_massmatrix_intrinsic = R"igl_Qu8mg5v7(

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

 Constructs the mass (area) matrix for a given mesh (V,F).
  
   Inputs:
     l  #l by simplex_size list of mesh edge lengths
     F  #F by simplex_size list of mesh elements (triangles or tetrahedra)
     type  one of the following ints:
       MASSMATRIX_TYPE_BARYCENTRIC  barycentric
       MASSMATRIX_TYPE_VORONOI voronoi-hybrid {default}
       MASSMATRIX_TYPE_FULL full {not implemented}
   Outputs: 
     M  #V by #V mass matrix
  
   See also: adjacency_matrix
  
)igl_Qu8mg5v7";

npe_function(massmatrix_intrinsic)
npe_doc(ds_massmatrix_intrinsic)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(type, igl::MassMatrixType)


npe_begin_code()

  Sparse_f64 m;
  igl::massmatrix_intrinsic(l, f, type, m);
  return npe::move(m);

npe_end_code()
#include <igl/massmatrix_intrinsic.h>

const char* ds_massmatrix_intrinsic = R"igl_Qu8mg5v7(

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

 Inputs:
     n  number of vertices (>= F.maxCoeff()+1)
)igl_Qu8mg5v7";

npe_function(massmatrix_intrinsic)
npe_doc(ds_massmatrix_intrinsic)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(type, igl::MassMatrixType)
npe_arg(n, int)


npe_begin_code()

  Sparse_f64 m;
  igl::massmatrix_intrinsic(l, f, type, n, m);
  return npe::move(m);

npe_end_code()


