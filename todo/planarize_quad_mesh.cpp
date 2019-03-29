#include <npe.h>
#include <typedefs.h>






#include <igl/planarize_quad_mesh.h>

const char* ds_planarize_quad_mesh = R"igl_Qu8mg5v7(

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

 Inputs:
     Vin        #V by 3 eigen Matrix of mesh vertex 3D positions
     F          #F by 4 eigen Matrix of face (quad) indices
     maxIter    maximum numbers of iterations
     threshold  minimum allowed threshold for non-planarity
   Output:
     Vout       #V by 3 eigen Matrix of planar mesh vertex 3D positions
  
)igl_Qu8mg5v7";

npe_function(planarize_quad_mesh)
npe_doc(ds_planarize_quad_mesh)

npe_arg(vin, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(max_iter, int)
npe_arg(threshold, double &)


npe_begin_code()

  EigenDense<npe_Scalar_> vout;
  igl::planarize_quad_mesh(vin, f, max_iter, threshold, vout);
  return npe::move(vout);

npe_end_code()


