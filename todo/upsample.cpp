#include <npe.h>
#include <typedefs.h>






#include <igl/upsample.h>

const char* ds_upsample = R"igl_Qu8mg5v7(

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

 Subdivide without moving vertices: Given the triangle mesh [V, F],
   where n_verts = V.rows(), computes newV and a sparse matrix S s.t.
   [newV, newF] is the subdivided mesh where newV = S*V.
  
   Inputs:
     n_verts  an integer (number of mesh vertices)
     F  an m by 3 matrix of integers of triangle faces
   Outputs:
     S  a sparse matrix (will become the subdivision matrix)
     newF  a matrix containing the new faces
)igl_Qu8mg5v7";

npe_function(upsample)
npe_doc(ds_upsample)

npe_arg(n_verts, int)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Eigen::SparseMatrix<SType> & s;
  EigenDense<npe_Scalar_> nf;
  igl::upsample(n_verts, f, s, nf);
  return std::make_tuple(npe::move(s), npe::move(nf));

npe_end_code()
#include <igl/upsample.h>

const char* ds_upsample = R"igl_Qu8mg5v7(

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

 Subdivide a mesh without moving vertices: loop subdivision but odd
   vertices stay put and even vertices are just edge midpoints
   
   Templates:
     MatV  matrix for vertex positions, e.g. MatrixXd
     MatF  matrix for vertex positions, e.g. MatrixXi
   Inputs:
     V  #V by dim  mesh vertices
     F  #F by 3  mesh triangles
   Outputs:
     NV new vertex positions, V is guaranteed to be at top
     NF new list of face indices
  
   NOTE: V should not be the same as NV,
   NOTE: F should not be the same as NF, use other proto
  
   Known issues:
     - assumes (V,F) is edge-manifold.
)igl_Qu8mg5v7";

npe_function(upsample)
npe_doc(ds_upsample)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(number_of_subdivs, int)


npe_begin_code()

  EigenDense<npe_Scalar_> nv;
  EigenDense<npe_Scalar_> nf;
  igl::upsample(v, f, number_of_subdivs, nv, nf);
  return std::make_tuple(npe::move(nv), npe::move(nf));

npe_end_code()
#include <igl/upsample.h>

const char* ds_upsample = R"igl_Qu8mg5v7(

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

 Virtually in place wrapper
)igl_Qu8mg5v7";

npe_function(upsample)
npe_doc(ds_upsample)

npe_arg(number_of_subdivs, int)


npe_begin_code()

  MatV & v;
  MatF & f;
  igl::upsample(number_of_subdivs, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


