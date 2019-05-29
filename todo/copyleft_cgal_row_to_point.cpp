#include <npe.h>
#include <typedefs.h>






#include <igl/row_to_point.h>

const char* ds_row_to_point = R"igl_Qu8mg5v7(

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

 Extract a row from V and treat as a 2D cgal point (only first two
       columns of V are used).
       
       Inputs:
         V  #V by 2 list of vertex positions
         i  row index
       Returns 2D cgal point
)igl_Qu8mg5v7";

npe_function(row_to_point)
npe_doc(ds_row_to_point)

npe_arg(v, dense_float, dense_double)
npe_arg(i, typename DerivedV::Index &)


npe_begin_code()

  igl::  copyleft::  cgal::row_to_point(v, i);
  return ;

npe_end_code()


