#include <npe.h>
#include <typedefs.h>






#include <igl/remesh_along_isoline.h>

const char* ds_remesh_along_isoline = R"igl_Qu8mg5v7(

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

 Given a triangle mesh and a scalar field, remesh so that a given isovalue
   of the scalar field follows (new) edges of the output mesh. Effectively
   running "marching triangles" on mesh, but not in any coherent order. The
   output mesh should be as manifold as the input.
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh triangle indices into V
     S  #V by 1 list of scalar field
     val  value of S to remesh along
   Outputs:
    U  #U by dim list of mesh vertex positions #U>=#V
    G  #G by 3 list of mesh triangle indices into U, #G>=#F
    SU  #U list of scalar field values over new mesh
    J  #G list of indices into G revealing birth triangles
    BC  #U by #V sparse matrix of barycentric coordinates so that U = BC*V
    L  #G list of bools whether scalar field in triangle below or above val
)igl_Qu8mg5v7";

npe_function(remesh_along_isoline)
npe_doc(ds_remesh_along_isoline)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(s, dense_float, dense_double)
npe_arg(val, typename DerivedS::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> u;
  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> su;
  EigenDense<npe_Scalar_> j;
  Eigen::SparseMatrix<BCtype> & bc;
  EigenDense<npe_Scalar_> l;
  igl::remesh_along_isoline(v, f, s, val, u, g, su, j, bc, l);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(su), npe::move(j), npe::move(bc), npe::move(l));

npe_end_code()
#include <igl/remesh_along_isoline.h>

const char* ds_remesh_along_isoline = R"igl_Qu8mg5v7(

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

 Input:
     n  number of vertices (#V)
)igl_Qu8mg5v7";

npe_function(remesh_along_isoline)
npe_doc(ds_remesh_along_isoline)

npe_arg(n, int)
npe_arg(f, dense_int, dense_long)
npe_arg(s, dense_float, dense_double)
npe_arg(val, typename DerivedS::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> su;
  EigenDense<npe_Scalar_> j;
  Eigen::SparseMatrix<BCtype> & bc;
  EigenDense<npe_Scalar_> l;
  igl::remesh_along_isoline(n, f, s, val, g, su, j, bc, l);
  return std::make_tuple(npe::move(g), npe::move(su), npe::move(j), npe::move(bc), npe::move(l));

npe_end_code()


