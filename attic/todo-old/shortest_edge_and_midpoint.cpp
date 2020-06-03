#include <npe.h>
#include <typedefs.h>






#include <igl/shortest_edge_and_midpoint.h>

const char* ds_shortest_edge_and_midpoint = R"igl_Qu8mg5v7(

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

 Cost and placement function compatible with igl::decimate. The cost of
   collapsing an edge is its length (prefer to collapse short edges) and the
   placement strategy for the new vertex is the midpoint of the collapsed
   edge.
  
   Inputs:
     e  index into E of edge to be considered for collapse
     V  #V by dim list of vertex positions
     F  #F by 3 list of faces (ignored)
     E  #E by 2 list of edge indices into V
     EMAP  #F*3 list of half-edges indices into E (ignored)
     EF  #E by 2 list of edge-face flaps into F (ignored)
     EI  #E by 2 list of edge-face opposite corners (ignored)
   Outputs:
     cost  set to edge length
     p  placed point set to edge midpoint
)igl_Qu8mg5v7";

npe_function(shortest_edge_and_midpoint)
npe_doc(ds_shortest_edge_and_midpoint)

npe_arg(e, int)
npe_arg(v, Eigen::MatrixXd &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(, Eigen::VectorXi &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(, Eigen::MatrixXi &)


npe_begin_code()

  double & cost;
  Eigen::RowVectorXd & p;
  igl::shortest_edge_and_midpoint(e, v, , e, , , , cost, p);
  return std::make_tuple(npe::move(cost), npe::move(p));

npe_end_code()


