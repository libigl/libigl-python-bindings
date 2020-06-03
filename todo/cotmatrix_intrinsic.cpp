#include <npe.h>
#include <typedefs.h>
#include <igl/cotmatrix_intrinsic.h>

const char* ds_cotmatrix_intrinsic = R"igl_Qu8mg5v7(

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

 Constructs the cotangent stiffness matrix (discrete laplacian) for a given
   mesh with faces F and edge lengths l.
  
   Inputs:
     l  #F by 3 list of (half-)edge lengths
     F  #F by 3 list of face indices into some (not necessarily
       determined/embedable) list of vertex positions V. It is assumed #V ==
       F.maxCoeff()+1
   Outputs:
     L  #V by #V sparse Laplacian matrix
  
   See also: cotmatrix, intrinsic_delaunay_cotmatrix
)igl_Qu8mg5v7";

npe_function(cotmatrix_intrinsic)
npe_doc(ds_cotmatrix_intrinsic)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Sparse_f64 l;
  igl::cotmatrix_intrinsic(l, f, l);
  return npe::move(l);

npe_end_code()


