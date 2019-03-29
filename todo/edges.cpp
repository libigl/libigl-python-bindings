#include <npe.h>
#include <typedefs.h>
#include <igl/edges.h>

const char* ds_edges = R"igl_Qu8mg5v7(

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

 Constructs a list of unique edges represented in a given mesh (V,F)
  
   Inputs:
     F  #F by 3 list of mesh faces (must be triangles)
     or
     T  #T x 4  matrix of indices of tet corners
   Outputs:
     E #E by 2 list of edges in no particular order
  
   See also: adjacency_matrix
)igl_Qu8mg5v7";

npe_function(edges)
npe_doc(ds_edges)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> e;
  igl::edges(f, e);
  return npe::move(e);

npe_end_code()


