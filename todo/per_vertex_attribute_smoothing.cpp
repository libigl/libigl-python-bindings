#include <npe.h>
#include <typedefs.h>
#include <igl/per_vertex_attribute_smoothing.h>

const char* ds_per_vertex_attribute_smoothing = R"igl_Qu8mg5v7(

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

 Smooth vertex attributes using uniform Laplacian
   Inputs:
     Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)
     F    #F by 3 eigne Matrix of face (triangle) indices
   Output:
     Aout #V by #A eigen Matrix of mesh vertex attributes
)igl_Qu8mg5v7";

npe_function(per_vertex_attribute_smoothing)
npe_doc(ds_per_vertex_attribute_smoothing)

npe_arg(ain, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> aout;
  igl::per_vertex_attribute_smoothing(ain, f, aout);
  return npe::move(aout);

npe_end_code()


