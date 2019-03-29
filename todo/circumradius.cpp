#include <npe.h>
#include <typedefs.h>
#include <igl/circumradius.h>

const char* ds_circumradius = R"igl_Qu8mg5v7(

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

 Compute the circumradius of each triangle in a mesh (V,F)
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by 3 list of triangle indices into V
   Outputs:
     R  #F list of circumradii
  
)igl_Qu8mg5v7";

npe_function(circumradius)
npe_doc(ds_circumradius)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  igl::circumradius(v, f, r);
  return npe::move(r);

npe_end_code()


