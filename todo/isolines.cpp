#include <npe.h>
#include <typedefs.h>
#include <igl/isolines.h>

const char* ds_isolines = R"igl_Qu8mg5v7(

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

 Constructs isolines for a function z given on a mesh (V,F)
    
    
     Inputs:
       V  #V by dim list of mesh vertex positions
       F  #F by 3 list of mesh faces (must be triangles)
       z  #V by 1 list of function values evaluated at vertices
       n  the number of desired isolines
     Outputs:
       isoV  #isoV by dim list of isoline vertex positions
       isoE  #isoE by 2 list of isoline edge positions
    
    
)igl_Qu8mg5v7";

npe_function(isolines)
npe_doc(ds_isolines)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(z, dense_f32, dense_f64)
npe_arg(n, int)


npe_begin_code()

  EigenDense<npe_Scalar_> iso_v;
  EigenDense<npe_Scalar_> iso_e;
  igl::isolines(v, f, z, n, iso_v, iso_e);
  return std::make_tuple(npe::move(iso_v), npe::move(iso_e));

npe_end_code()


