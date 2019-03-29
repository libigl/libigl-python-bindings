#include <npe.h>
#include <typedefs.h>
#include <igl/local_basis.h>

const char* ds_local_basis = R"igl_Qu8mg5v7(

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

 Compute a local orthogonal reference system for each triangle in the given mesh
   Templates:
     DerivedV derived from vertex positions matrix type: i.e. MatrixXd
     DerivedF derived from face indices matrix type: i.e. MatrixXi
   Inputs:
     V  eigen matrix #V by 3
     F  #F by 3 list of mesh faces (must be triangles)
   Outputs:
     B1 eigen matrix #F by 3, each vector is tangent to the triangle
     B2 eigen matrix #F by 3, each vector is tangent to the triangle and perpendicular to B1
     B3 eigen matrix #F by 3, normal of the triangle
  
   See also: adjacency_matrix
)igl_Qu8mg5v7";

npe_function(local_basis)
npe_doc(ds_local_basis)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> b1;
  EigenDense<npe_Scalar_> b2;
  EigenDense<npe_Scalar_> b3;
  igl::local_basis(v, f, b1, b2, b3);
  return std::make_tuple(npe::move(b1), npe::move(b2), npe::move(b3));

npe_end_code()


