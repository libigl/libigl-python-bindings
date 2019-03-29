#include <npe.h>
#include <typedefs.h>
#include <igl/project_isometrically_to_plane.h>

const char* ds_project_isometrically_to_plane = R"igl_Qu8mg5v7(

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

 Project each triangle to the plane
  
   [U,UF,I] = project_isometrically_to_plane(V,F)
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of mesh indices
   Outputs:
     U  #F*3 by 2 list of triangle positions
     UF  #F by 3 list of mesh indices into U
     I  #V by #F such that I(i,j) = 1 implies U(j,:) corresponds to V(i,:)
  
)igl_Qu8mg5v7";

npe_function(project_isometrically_to_plane)
npe_doc(ds_project_isometrically_to_plane)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> u;
  EigenDense<npe_Scalar_> uf;
  Sparse_f64 i;
  igl::project_isometrically_to_plane(v, f, u, uf, i);
  return std::make_tuple(npe::move(u), npe::move(uf), npe::move(i));

npe_end_code()


