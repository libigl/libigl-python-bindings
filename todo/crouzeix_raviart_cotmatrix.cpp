#include <npe.h>
#include <typedefs.h>






#include <igl/crouzeix_raviart_cotmatrix.h>

const char* ds_crouzeix_raviart_cotmatrix = R"igl_Qu8mg5v7(

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

 CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent
   stiffness matrix.
  
   See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
   Harmon, Zorin, Grinspun 2007]
  
   Inputs:
     V  #V by dim list of vertex positions
     F  #F by 3/4 list of triangle/tetrahedron indices
   Outputs:
     L  #E by #E edge/face-based diagonal cotangent matrix
     E  #E by 2/3 list of edges/faces
     EMAP  #F*3/4 list of indices mapping allE to E
  
   See also: crouzeix_raviart_massmatrix
)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_cotmatrix)
npe_doc(ds_crouzeix_raviart_cotmatrix)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Eigen::SparseMatrix<LT> & l;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  igl::crouzeix_raviart_cotmatrix(v, f, l, e, emap);
  return std::make_tuple(npe::move(l), npe::move(e), npe::move(emap));

npe_end_code()
#include <igl/crouzeix_raviart_cotmatrix.h>

const char* ds_crouzeix_raviart_cotmatrix = R"igl_Qu8mg5v7(

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

 wrapper if E and EMAP are already computed (better match!)
)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_cotmatrix)
npe_doc(ds_crouzeix_raviart_cotmatrix)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(e, dense_f32, dense_f64)
npe_arg(emap, dense_f32, dense_f64)


npe_begin_code()

  Eigen::SparseMatrix<LT> & l;
  igl::crouzeix_raviart_cotmatrix(v, f, e, emap, l);
  return npe::move(l);

npe_end_code()


