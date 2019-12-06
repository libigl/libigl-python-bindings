#include <npe.h>
#include <typedefs.h>






#include <igl/incircle.h>

const char* ds_incircle = R"igl_Qu8mg5v7(

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
         pa,pb,pc,pd  2D points.
       Output:
         1 if pd is inside of the oriented circle formed by pa,pb,pc.
         0 if pd is co-circular with pa,pb,pc.
        -1 if pd is outside of the oriented circle formed by pa,pb,pc.
)igl_Qu8mg5v7";

npe_function(incircle)
npe_doc(ds_incircle)

npe_arg(pa, Scalar [2])
npe_arg(pb, Scalar [2])
npe_arg(pc, Scalar [2])
npe_arg(pd, Scalar [2])


npe_begin_code()

  igl::  copyleft::  cgal::incircle(pa, pb, pc, pd);
  return ;

npe_end_code()


