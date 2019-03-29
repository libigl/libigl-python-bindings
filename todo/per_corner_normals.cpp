#include <npe.h>
#include <typedefs.h>






#include <igl/per_corner_normals.h>

const char* ds_per_corner_normals = R"igl_Qu8mg5v7(

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

 Compute vertex normals via vertex position list, face list
   Inputs:
     V  #V by 3 eigen Matrix of mesh vertex 3D positions
     F  #F by 3 eigen Matrix of face (triangle) indices
     corner_threshold  threshold in degrees on sharp angles
   Output:
     CN  #F*3 by 3 eigen Matrix of mesh vertex 3D normals, where the normal
       for corner F(i,j) is at CN(i*3+j,:) 
)igl_Qu8mg5v7";

npe_function(per_corner_normals)
npe_doc(ds_per_corner_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(corner_threshold, double)


npe_begin_code()

  EigenDense<npe_Scalar_> cn;
  igl::per_corner_normals(v, f, corner_threshold, cn);
  return npe::move(cn);

npe_end_code()
#include <igl/per_corner_normals.h>

const char* ds_per_corner_normals = R"igl_Qu8mg5v7(

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

 Other Inputs:
     FN  #F by 3 eigen Matrix of face normals
)igl_Qu8mg5v7";

npe_function(per_corner_normals)
npe_doc(ds_per_corner_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(fn, dense_f32, dense_f64)
npe_arg(corner_threshold, double)


npe_begin_code()

  EigenDense<npe_Scalar_> cn;
  igl::per_corner_normals(v, f, fn, corner_threshold, cn);
  return npe::move(cn);

npe_end_code()
#include <igl/per_corner_normals.h>

const char* ds_per_corner_normals = R"igl_Qu8mg5v7(

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

 Other Inputs:
     VF  map from vertices to list of incident faces
)igl_Qu8mg5v7";

npe_function(per_corner_normals)
npe_doc(ds_per_corner_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(fn, dense_f32, dense_f64)
npe_arg(vf, std::vector<std::vector<IndexType> > &)
npe_arg(corner_threshold, double)


npe_begin_code()

  EigenDense<npe_Scalar_> cn;
  igl::per_corner_normals(v, f, fn, vf, corner_threshold, cn);
  return npe::move(cn);

npe_end_code()


