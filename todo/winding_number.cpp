#include <npe.h>
#include <typedefs.h>
#include <igl/winding_number.h>

const char* ds_winding_number = R"igl_Qu8mg5v7(

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

 WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron
   described by points (vectors) V
  
   Templates:
     dim  dimension of input
   Inputs:
    V  n by 3 list of vertex positions
    F  #F by 3 list of triangle indices, minimum index is 0
    O  no by 3 list of origin positions
   Outputs:
    S  no by 1 list of winding numbers
  
)igl_Qu8mg5v7";

npe_function(winding_number)
npe_doc(ds_winding_number)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(o, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::winding_number(v, f, o, w);
  return npe::move(w);

npe_end_code()
#include <igl/winding_number.h>

const char* ds_winding_number = R"igl_Qu8mg5v7(

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

 Compute winding number of a single point
  
   Inputs:
    V  n by dim list of vertex positions
    F  #F by dim list of triangle indices, minimum index is 0
    p  single origin position
   Outputs:
    w  winding number of this point
  
)igl_Qu8mg5v7";

npe_function(winding_number)
npe_doc(ds_winding_number)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(p, dense_f32, dense_f64)


npe_begin_code()

  igl::winding_number(v, f, p);
  return ;

npe_end_code()


