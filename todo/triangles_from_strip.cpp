#include <npe.h>
#include <typedefs.h>
#include <igl/triangles_from_strip.h>

const char* ds_triangles_from_strip = R"igl_Qu8mg5v7(

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

 TRIANGLES_FROM_STRIP Create a list of triangles from a stream of indices
   along a strip.
  
   Inputs:
     S  #S list of indices
   Outputs:
     F  #S-2 by 3 list of triangle indices
  
)igl_Qu8mg5v7";

npe_function(triangles_from_strip)
npe_doc(ds_triangles_from_strip)

npe_arg(s, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::triangles_from_strip(s, f);
  return npe::move(f);

npe_end_code()


