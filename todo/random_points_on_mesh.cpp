#include <npe.h>
#include <typedefs.h>
#include <igl/random_points_on_mesh.h>

const char* ds_random_points_on_mesh = R"igl_Qu8mg5v7(

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

 RANDOM_POINTS_ON_MESH Randomly sample a mesh (V,F) n times.
  
   Inputs:
     n  number of samples
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of mesh triangle indices
   Outputs:
     B  n by 3 list of barycentric coordinates, ith row are coordinates of
       ith sampled point in face FI(i)
     FI  n list of indices into F 
  
)igl_Qu8mg5v7";

npe_function(random_points_on_mesh)
npe_doc(ds_random_points_on_mesh)

npe_arg(n, int)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> b;
  EigenDense<npe_Scalar_> fi;
  igl::random_points_on_mesh(n, v, f, b, fi);
  return std::make_tuple(npe::move(b), npe::move(fi));

npe_end_code()






#include <igl/random_points_on_mesh.h>

const char* ds_random_points_on_mesh = R"igl_Qu8mg5v7(

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

 Outputs:
     B n by #V sparse matrix so that  B*V produces a list of sample points
)igl_Qu8mg5v7";

npe_function(random_points_on_mesh)
npe_doc(ds_random_points_on_mesh)

npe_arg(n, int)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Eigen::SparseMatrix<ScalarB> & b;
  EigenDense<npe_Scalar_> fi;
  igl::random_points_on_mesh(n, v, f, b, fi);
  return std::make_tuple(npe::move(b), npe::move(fi));

npe_end_code()


