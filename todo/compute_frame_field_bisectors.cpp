#include <npe.h>
#include <typedefs.h>
#include <igl/compute_frame_field_bisectors.h>

const char* ds_compute_frame_field_bisectors = R"igl_Qu8mg5v7(

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

 Compute bisectors of a frame field defined on mesh faces
   Inputs:
     V     #V by 3 eigen Matrix of mesh vertex 3D positions
     F     #F by 3 eigen Matrix of face (triangle) indices
     B1    #F by 3 eigen Matrix of face (triangle) base vector 1
     B2    #F by 3 eigen Matrix of face (triangle) base vector 2
     PD1   #F by 3 eigen Matrix of the first per face frame field vector
     PD2   #F by 3 eigen Matrix of the second per face frame field vector
   Output:
     BIS1  #F by 3 eigen Matrix of the first per face frame field bisector
     BIS2  #F by 3 eigen Matrix of the second per face frame field bisector
  
)igl_Qu8mg5v7";

npe_function(compute_frame_field_bisectors)
npe_doc(ds_compute_frame_field_bisectors)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(b1, dense_f32, dense_f64)
npe_arg(b2, dense_f32, dense_f64)
npe_arg(pd1, dense_f32, dense_f64)
npe_arg(pd2, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> bis1;
  EigenDense<npe_Scalar_> bis2;
  igl::compute_frame_field_bisectors(v, f, b1, b2, pd1, pd2, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()
#include <igl/compute_frame_field_bisectors.h>

const char* ds_compute_frame_field_bisectors = R"igl_Qu8mg5v7(

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

 Wrapper without given basis vectors.
)igl_Qu8mg5v7";

npe_function(compute_frame_field_bisectors)
npe_doc(ds_compute_frame_field_bisectors)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(pd1, dense_f32, dense_f64)
npe_arg(pd2, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> bis1;
  EigenDense<npe_Scalar_> bis2;
  igl::compute_frame_field_bisectors(v, f, pd1, pd2, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()


