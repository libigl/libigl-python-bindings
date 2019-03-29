#include <npe.h>
#include <typedefs.h>






#include <igl/progressive_hulls_cost_and_placement.h>

const char* ds_progressive_hulls_cost_and_placement = R"igl_Qu8mg5v7(

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

 A "cost and placement" compatible with `igl::decimate` implementing the
     "progressive hulls" algorithm in "Silhouette clipping" [Sander et al.
     2000]. This implementation fixes an issue that the original linear
     program becomes unstable for flat patches by introducing a small
     quadratic energy term pulling the collapsed edge toward its midpoint.
     This function is not really meant to be called directly but rather
     passed to `igl::decimate` as a handle.
    
     Inputs:
       e  index of edge to be collapsed
       V  #V by 3 list of vertex positions
       F  #F by 3 list of faces indices into V
       E  #E by 3 list of edges indices into V
       EMAP #F*3 list of indices into E, mapping each directed edge to unique
         unique edge in E
       EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
         F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
         e=(j->i)
       EI  #E by 2 list of edge flap corners (see above).
     Outputs:
       cost  cost of collapsing edge e
       p  position to place collapsed vertex
    
)igl_Qu8mg5v7";

npe_function(progressive_hulls_cost_and_placement)
npe_doc(ds_progressive_hulls_cost_and_placement)

npe_arg(e, int)
npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)
npe_arg(ef, Eigen::MatrixXi &)
npe_arg(ei, Eigen::MatrixXi &)


npe_begin_code()

  double & cost;
  Eigen::RowVectorXd & p;
  igl::  copyleft::progressive_hulls_cost_and_placement(e, v, f, e, emap, ef, ei, cost, p);
  return std::make_tuple(npe::move(cost), npe::move(p));

npe_end_code()


