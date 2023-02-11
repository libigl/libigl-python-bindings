// might be sparse matrix problem

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/hessian_energy.h>

const char* ds_hessian_energy = R"igl_Qu8mg5v7(

Constructs the Hessian energy matrix using mixed FEM
  as described in https:arxiv.org/abs/1707.04348
  Natural Boundary Conditions for Smoothing in Geometry Processing
  (Oded Stein, Eitan Grinspun, Max Wardetzky, Alec Jacobson)

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh faces (must be triangles)


Returns
-------
Q  #V by #V Hessian energy matrix, each row/column i
  corresponding to V(i,:)


See also
--------


Notes
-----
None

Examples
--------

    
)igl_Qu8mg5v7";

npe_function(hessian_energy)
npe_doc(ds_hessian_energy)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  
  EigenSparseLike<npe_Matrix_v> q;
  igl::hessian_energy(v, f, q);
  return npe::move(q);

npe_end_code()


