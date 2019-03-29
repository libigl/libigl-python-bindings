#include <npe.h>
#include <typedefs.h>






#include <igl/exterior_edges.h>

const char* ds_exterior_edges = R"igl_Qu8mg5v7(

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

 EXTERIOR_EDGES Determines boundary "edges" and also edges with an
   odd number of occurrences where seeing edge (i,j) counts as +1 and seeing
   the opposite edge (j,i) counts as -1
  
   Inputs:
     F  #F by simplex_size list of "faces"
   Outputs:
     E  #E by simplex_size-1  list of exterior edges
  
)igl_Qu8mg5v7";

npe_function(exterior_edges)
npe_doc(ds_exterior_edges)

npe_arg(f, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXi & e;
  igl::exterior_edges(f, e);
  return npe::move(e);

npe_end_code()
#include <igl/exterior_edges.h>

const char* ds_exterior_edges = R"igl_Qu8mg5v7(

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

 Inline version
)igl_Qu8mg5v7";

npe_function(exterior_edges)
npe_doc(ds_exterior_edges)

npe_arg(f, Eigen::MatrixXi &)


npe_begin_code()

  igl::exterior_edges(f);
  return ;

npe_end_code()


