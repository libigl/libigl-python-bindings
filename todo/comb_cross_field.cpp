#include <npe.h>
#include <typedefs.h>
#include <igl/comb_cross_field.h>

const char* ds_comb_cross_field = R"igl_Qu8mg5v7(

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
     V          #V by 3 eigen Matrix of mesh vertex 3D positions
     F          #F by 4 eigen Matrix of face (quad) indices
     PD1in      #F by 3 eigen Matrix of the first per face cross field vector
     PD2in      #F by 3 eigen Matrix of the second per face cross field vector
   Output:
     PD1out      #F by 3 eigen Matrix of the first combed cross field vector
     PD2out      #F by 3 eigen Matrix of the second combed cross field vector
  
)igl_Qu8mg5v7";

npe_function(comb_cross_field)
npe_doc(ds_comb_cross_field)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(pd1in, dense_f32, dense_f64)
npe_arg(pd2in, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> pd1out;
  EigenDense<npe_Scalar_> pd2out;
  igl::comb_cross_field(v, f, pd1in, pd2in, pd1out, pd2out);
  return std::make_tuple(npe::move(pd1out), npe::move(pd2out));

npe_end_code()


