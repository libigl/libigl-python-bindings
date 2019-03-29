#include <npe.h>
#include <typedefs.h>
#include <igl/directed_edge_parents.h>

const char* ds_directed_edge_parents = R"igl_Qu8mg5v7(

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

 Recover "parents" (preceding edges) in a tree given just directed edges.
  
   Inputs:
     E  #E by 2 list of directed edges
   Outputs:
     P  #E list of parent indices into E (-1) means root
  
)igl_Qu8mg5v7";

npe_function(directed_edge_parents)
npe_doc(ds_directed_edge_parents)

npe_arg(e, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::directed_edge_parents(e, p);
  return npe::move(p);

npe_end_code()


