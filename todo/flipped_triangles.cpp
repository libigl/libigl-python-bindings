#include <npe.h>
#include <typedefs.h>
#include <igl/flipped_triangles.h>

const char* ds_flipped_triangles = R"igl_Qu8mg5v7(

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

 Finds the ids of the flipped triangles of the mesh V,F in the UV mapping uv
  
   Inputs:
     V  #V by 2 list of mesh vertex positions
     F  #F by 3 list of mesh faces (must be triangles)
   Outputs:
     X  #flipped list of containing the indices into F of the flipped triangles
   Wrapper with return type
)igl_Qu8mg5v7";

npe_function(flipped_triangles)
npe_doc(ds_flipped_triangles)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> x;
  igl::flipped_triangles(v, f, x);
  return npe::move(x);

npe_end_code()
#include <igl/flipped_triangles.h>

const char* ds_flipped_triangles = R"igl_Qu8mg5v7(
See flipped_triangles for the documentation.
)igl_Qu8mg5v7";

npe_function(flipped_triangles)
npe_doc(ds_flipped_triangles)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  igl::flipped_triangles(v, f);
  return ;

npe_end_code()


