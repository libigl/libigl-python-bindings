#include <npe.h>
#include <typedefs.h>
#include <igl/hessian.h>

const char* ds_hessian = R"igl_Qu8mg5v7(

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

 Constructs the finite element Hessian matrix
     as described in https:arxiv.org/abs/1707.04348,
     Natural Boundary Conditions for Smoothing in Geometry Processing
     (Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)
     The interior vertices are NOT set to zero yet.
    
     Inputs:
       V  #V by dim list of mesh vertex positions
       F  #F by 3 list of mesh faces (must be triangles)
     Outputs:
       H  #V by #V Hessian energy matrix, each column i
         corresponding to V(i,:)
    
    
    
)igl_Qu8mg5v7";

npe_function(hessian)
npe_doc(ds_hessian)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Sparse_f64 h;
  igl::hessian(v, f, h);
  return npe::move(h);

npe_end_code()


