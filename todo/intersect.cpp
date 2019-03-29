#include <npe.h>
#include <typedefs.h>






#include <igl/intersect.h>

const char* ds_intersect = R"igl_Qu8mg5v7(

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

 Determine the intersect between two sets of coefficients using ==
   Templates:
     M  matrix type that implements indexing by global index M(i)
   Inputs:
     A  matrix of coefficients
     B  matrix of coefficients
   Output:
     C  matrix of elements appearing in both A and B, C is always resized to
     have a single column
)igl_Qu8mg5v7";

npe_function(intersect)
npe_doc(ds_intersect)

npe_arg(a, M &)
npe_arg(b, M &)


npe_begin_code()

  M & c;
  igl::intersect(a, b, c);
  return npe::move(c);

npe_end_code()
#include <igl/intersect.h>

const char* ds_intersect = R"igl_Qu8mg5v7(

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

 Last argument as return
)igl_Qu8mg5v7";

npe_function(intersect)
npe_doc(ds_intersect)

npe_arg(a, M &)
npe_arg(b, M &)


npe_begin_code()

  igl::intersect(a, b);
  return ;

npe_end_code()


