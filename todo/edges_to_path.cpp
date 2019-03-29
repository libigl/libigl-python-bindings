#include <npe.h>
#include <typedefs.h>
#include <igl/edges_to_path.h>

const char* ds_edges_to_path = R"igl_Qu8mg5v7(

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

 EDGES_TO_PATH Given a set of undirected, unique edges such that all form a
   single connected compoent with exactly 0 or 2 nodes with valence =1,
   determine the/a path visiting all nodes.
  
   Inputs:
     E  #E by 2 list of undirected edges
   Outputs:
     I  #E+1 list of nodes in order tracing the chain (loop), if the output
       is a loop then I(1) == I(end)
     J  #I-1 list of indices into E of edges tracing I
     K  #I-1 list of indices into columns of E {1,2} so that K(i) means that
       E(i,K(i)) comes before the other (i.e., E(i,3-K(i)) ). This means that 
       I(i) == E(J(i),K(i)) for i<#I, or
       I == E(sub2ind(size(E),J([1:end end]),[K;3-K(end)]))))
   
)igl_Qu8mg5v7";

npe_function(edges_to_path)
npe_doc(ds_edges_to_path)

npe_arg(e, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> k;
  igl::edges_to_path(e, i, j, k);
  return std::make_tuple(npe::move(i), npe::move(j), npe::move(k));

npe_end_code()


