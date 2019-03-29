#include <npe.h>
#include <typedefs.h>






#include <igl/edge_collapse_is_valid.h>

const char* ds_edge_collapse_is_valid = R"igl_Qu8mg5v7(

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

 Assumes (V,F) is a closed manifold mesh (except for previouslly collapsed
   faces which should be set to: 
   [IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL].
   Tests whether collapsing exactly two faces and exactly 3 edges from E (e
   and one side of each face gets collapsed to the other) will result in a
   mesh with the same topology.
  
   Inputs:
     e  index into E of edge to try to collapse. E(e,:) = [s d] or [d s] so
       that s<d, then d is collapsed to s.
     F  #F by 3 list of face indices into V.
     E  #E by 2 list of edge indices into V.
     EMAP #F*3 list of indices into E, mapping each directed edge to unique
       unique edge in E
     EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
       F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
       e=(j->i)
     EI  #E by 2 list of edge flap corners (see above).
   Returns true if edge collapse is valid
)igl_Qu8mg5v7";

npe_function(edge_collapse_is_valid)
npe_doc(ds_edge_collapse_is_valid)

npe_arg(e, int)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)
npe_arg(ef, Eigen::MatrixXi &)
npe_arg(ei, Eigen::MatrixXi &)


npe_begin_code()

  igl::edge_collapse_is_valid(e, f, e, emap, ef, ei);
  return ;

npe_end_code()


