#include <npe.h>
#include <typedefs.h>






#include <igl/edge_exists_near.h>

const char* ds_edge_exists_near = R"igl_Qu8mg5v7(

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

 Does edge (a,b) exist in the edges of all faces incident on
   existing unique edge uei.
  
   Inputs:
     uE  #uE by 2 list of unique undirected edges
     EMAP #F*3 list of indices into uE, mapping each directed edge to unique
       undirected edge
     uE2E  #uE list of lists of indices into E of coexisting edges
     E  #F*3 by 2 list of half-edges
     a  1st end-point of query edge
     b  2nd end-point of query edge
     uei  index into uE/uE2E of unique edge
   Returns true if edge exists near uei.
  
   See also: unique_edge_map
)igl_Qu8mg5v7";

npe_function(edge_exists_near)
npe_doc(ds_edge_exists_near)

npe_arg(u_e, dense_f32, dense_f64)
npe_arg(emap, dense_f32, dense_f64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(a, Index &)
npe_arg(b, Index &)
npe_arg(uei, Index &)


npe_begin_code()

  igl::edge_exists_near(u_e, emap, u_e2_e, a, b, uei);
  return ;

npe_end_code()


