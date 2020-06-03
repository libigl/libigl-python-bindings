#include <npe.h>
#include <typedefs.h>






#include <igl/connected_components.h>

const char* ds_connected_components = R"igl_Qu8mg5v7(

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

 Determine the connected components of a graph described by the input
   adjacency matrix (similar to MATLAB's graphconncomp).
  
   Inputs:
      A  #A by #A adjacency matrix (treated as describing an undirected graph)
   Outputs:
      C  #A list of component indices into [0,#K-1]
      K  #K list of sizes of each component
   Returns number of connected components
)igl_Qu8mg5v7";

npe_function(connected_components)
npe_doc(ds_connected_components)

npe_arg(a, Eigen::SparseMatrix<Atype> &)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> k;
  igl::connected_components(a, c, k);
  return std::make_tuple(npe::move(c), npe::move(k));

npe_end_code()


