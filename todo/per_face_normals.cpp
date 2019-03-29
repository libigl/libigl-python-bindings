#include <npe.h>
#include <typedefs.h>
#include <igl/per_face_normals.h>

const char* ds_per_face_normals = R"igl_Qu8mg5v7(

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

 Compute face normals via vertex position list, face list
   Inputs:
     V  #V by 3 eigen Matrix of mesh vertex 3D positions
     F  #F by 3 eigen Matrix of face (triangle) indices
     Z  3 vector normal given to faces with degenerate normal.
   Output:
     N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals
  
   Example:
      Give degenerate faces (1/3,1/3,1/3)^0.5
     per_face_normals(V,F,Vector3d(1,1,1).normalized(),N);
)igl_Qu8mg5v7";

npe_function(per_face_normals)
npe_doc(ds_per_face_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(z, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_face_normals(v, f, z, n);
  return npe::move(n);

npe_end_code()
#include <igl/per_face_normals.h>

const char* ds_per_face_normals = R"igl_Qu8mg5v7(

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

 Wrapper with Z = (0,0,0). Note that this means that row norms will be zero
   (i.e. not 1) for degenerate normals.
)igl_Qu8mg5v7";

npe_function(per_face_normals)
npe_doc(ds_per_face_normals)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_face_normals(v, f, n);
  return npe::move(n);

npe_end_code()
#include <igl/per_face_normals_stable.h>

const char* ds_per_face_normals_stable = R"igl_Qu8mg5v7(

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

 Special version where order of face indices is guaranteed not to effect
   output.
)igl_Qu8mg5v7";

npe_function(per_face_normals_stable)
npe_doc(ds_per_face_normals_stable)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  igl::per_face_normals_stable(v, f, n);
  return npe::move(n);

npe_end_code()


