#include <npe.h>
#include <typedefs.h>
#include <igl/comb_frame_field.h>

const char* ds_comb_frame_field = R"igl_Qu8mg5v7(

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
     V            #V by 3 eigen Matrix of mesh vertex 3D positions
     F            #F by 4 eigen Matrix of face (quad) indices
     PD1          #F by 3 eigen Matrix of the first per face cross field vector
     PD2          #F by 3 eigen Matrix of the second per face cross field vector
     BIS1_combed  #F by 3 eigen Matrix of the first combed bisector field vector
     BIS2_combed  #F by 3 eigen Matrix of the second combed bisector field vector
   Output:
     PD1_combed  #F by 3 eigen Matrix of the first combed cross field vector
     PD2_combed  #F by 3 eigen Matrix of the second combed cross field vector
  
)igl_Qu8mg5v7";

npe_function(comb_frame_field)
npe_doc(ds_comb_frame_field)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(pd1, dense_f32, dense_f64)
npe_arg(pd2, dense_f32, dense_f64)
npe_arg(bis1_combed, dense_f32, dense_f64)
npe_arg(bis2_combed, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> pd1_combed;
  EigenDense<npe_Scalar_> pd2_combed;
  igl::comb_frame_field(v, f, pd1, pd2, bis1_combed, bis2_combed, pd1_combed, pd2_combed);
  return std::make_tuple(npe::move(pd1_combed), npe::move(pd2_combed));

npe_end_code()


