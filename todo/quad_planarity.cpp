#include <npe.h>
#include <typedefs.h>
#include <igl/quad_planarity.h>

const char* ds_quad_planarity = R"igl_Qu8mg5v7(

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

 Compute planarity of the faces of a quad mesh
   Inputs:
     V  #V by 3 eigen Matrix of mesh vertex 3D positions
     F  #F by 4 eigen Matrix of face (quad) indices
   Output:
     P  #F by 1 eigen Matrix of mesh face (quad) planarities
  
)igl_Qu8mg5v7";

npe_function(quad_planarity)
npe_doc(ds_quad_planarity)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::quad_planarity(v, f, p);
  return npe::move(p);

npe_end_code()


