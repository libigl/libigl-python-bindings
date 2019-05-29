#include <npe.h>
#include <typedefs.h>
#include <igl/piecewise_constant_winding_number.h>

const char* ds_piecewise_constant_winding_number = R"igl_Qu8mg5v7(

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

 PIECEWISE_CONSTANT_WINDING_NUMBER Determine if a given mesh induces a
       piecewise constant winding number field: Is this mesh valid input to
       solid set operations.
       
       Inputs:
         V  #V by 3 list of mesh vertex positions
         F  #F by 3 list of triangle indices into V
       Returns true if the mesh _combinatorially_ induces a piecewise
       constant winding number field.
)igl_Qu8mg5v7";

npe_function(piecewise_constant_winding_number)
npe_doc(ds_piecewise_constant_winding_number)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  igl::  copyleft::  cgal::piecewise_constant_winding_number(v, f);
  return ;

npe_end_code()


