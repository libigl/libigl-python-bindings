#include <npe.h>
#include <typedefs.h>






#include <igl/edge_flaps.h>

const char* ds_edge_flaps = R"igl_Qu8mg5v7(

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

 Determine "edge flaps": two faces on either side of a unique edge (assumes
   edge-manifold mesh)
  
   Inputs:
     F  #F by 3 list of face indices
     E  #E by 2 list of edge indices into V.
     EMAP #F*3 list of indices into E, mapping each directed edge to unique
       unique edge in E
   Outputs:
     EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
       F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
       e=(j->i)
     EI  #E by 2 list of edge flap corners (see above).
  
   TODO: This seems to be a duplicate of edge_topology.h
   igl::edge_topology(V,F,etEV,etFE,etEF);
   igl::edge_flaps(F,efE,efEMAP,efEF,efEI);
   [~,I] = sort(efE,2)
   all( efE(sub2ind(size(efE),repmat(1:size(efE,1),2,1)',I)) == etEV )
   all( efEF(sub2ind(size(efE),repmat(1:size(efE,1),2,1)',I)) == etEF )
   all(efEMAP(sub2ind(size(F),repmat(1:size(F,1),3,1)',repmat([1 2 3],size(F,1),1))) == etFE(:,[2 3 1]))
)igl_Qu8mg5v7";

npe_function(edge_flaps)
npe_doc(ds_edge_flaps)

npe_arg(f, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)


npe_begin_code()

  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  igl::edge_flaps(f, e, emap, ef, ei);
  return std::make_tuple(npe::move(ef), npe::move(ei));

npe_end_code()
#include <igl/edge_flaps.h>

const char* ds_edge_flaps = R"igl_Qu8mg5v7(

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

 Only faces as input
)igl_Qu8mg5v7";

npe_function(edge_flaps)
npe_doc(ds_edge_flaps)

npe_arg(f, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  igl::edge_flaps(f, e, emap, ef, ei);
  return std::make_tuple(npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei));

npe_end_code()


