// TODO: __example __bug conflict type
#include <npe.h>
#include <typedefs.h>
#include <igl/compute_frame_field_bisectors.h>

const char* ds_compute_frame_field_bisectors = R"igl_Qu8mg5v7(

Compute bisectors of a frame field defined on mesh faces

Parameters
----------
V     #V by 3 eigen Matrix of mesh vertex 3D positions
F     #F by 3 eigen Matrix of face (triangle) indices
B1    #F by 3 eigen Matrix of face (triangle) base vector 1
B2    #F by 3 eigen Matrix of face (triangle) base vector 2
PD1   #F by 3 eigen Matrix of the first per face frame field vector
PD2   #F by 3 eigen Matrix of the second per face frame field vector

Returns
-------
BIS1  #F by 3 eigen Matrix of the first per face frame field bisector
BIS2  #F by 3 eigen Matrix of the second per face frame field bisector

See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(compute_frame_field_bisectors)
npe_doc(ds_compute_frame_field_bisectors)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(b1, npe_matches(v))
npe_arg(b2, npe_matches(v))
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))


npe_begin_code()

  npe_Matrix_v bis1;
  npe_Matrix_v bis2;
  igl::compute_frame_field_bisectors(v, f, b1, b2, pd1, pd2, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()



const char* ds_compute_frame_field_bisectors_no_basis = R"igl_Qu8mg5v7(

Wrapper without given basis vectors.

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

)igl_Qu8mg5v7";

npe_function(compute_frame_field_bisectors_no_basis)
npe_doc(ds_compute_frame_field_bisectors_no_basis)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1, npe_matches(v))
npe_arg(pd2, npe_matches(v))


npe_begin_code()

  npe_Matrix_v bis1;
  npe_Matrix_v bis2;
  igl::compute_frame_field_bisectors(v, f, pd1, pd2, bis1, bis2);
  return std::make_tuple(npe::move(bis1), npe::move(bis2));

npe_end_code()


