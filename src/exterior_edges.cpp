// need assertion for a.rows = b.rows-1
// __copy
#include <npe.h>
#include <typedefs.h>
#include <common.h>





#include <igl/exterior_edges.h>

const char* ds_exterior_edges = R"igl_Qu8mg5v7(

EXTERIOR_EDGES Determines boundary "edges" and also edges with an
  odd number of occurrences where seeing edge (i,j) counts as +1 and seeing
  the opposite edge (j,i) counts as -1

Parameters
----------
F  #F by simplex_size list of "faces"

Returns
-------
E  #E by simplex_size-1  list of exterior edges

See also
--------


Notes
-----
None

Examples
--------

  
  
)igl_Qu8mg5v7";

npe_function(exterior_edges)
npe_doc(ds_exterior_edges)

npe_arg(f, dense_int, dense_long, dense_longlong)

npe_begin_code()

  npe_Matrix_f e;
  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  igl::exterior_edges(f_copy, e_copy);
  return npe::move(e_copy);

npe_end_code()

