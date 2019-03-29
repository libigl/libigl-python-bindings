#include <npe.h>
#include <typedefs.h>






#include <igl/circulation.h>

const char* ds_circulation = R"igl_Qu8mg5v7(

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

 Return list of faces around the end point of an edge. Assumes
   data-structures are built from an edge-manifold **closed** mesh.
  
   Inputs:
     e  index into E of edge to circulate
     ccw  whether to _continue_ in ccw direction of edge (circulate around
       E(e,1))
     F  #F by 3 list of face indices
     E  #E by 2 list of edge indices
     EMAP #F*3 list of indices into E, mapping each directed edge to unique
       unique edge in E
     EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
       F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
       e=(j->i)
     EI  #E by 2 list of edge flap corners (see above).
   Returns list of faces touched by circulation (in cyclically order).
     
)igl_Qu8mg5v7";

npe_function(circulation)
npe_doc(ds_circulation)

npe_arg(e, int)
npe_arg(ccw, bool)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)
npe_arg(ef, Eigen::MatrixXi &)
npe_arg(ei, Eigen::MatrixXi &)


npe_begin_code()

  igl::circulation(e, ccw, f, e, emap, ef, ei);
  return ;

npe_end_code()
#include <igl/circulation.h>

const char* ds_circulation = R"igl_Qu8mg5v7(

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

 Wrapper with VectorXi output.
)igl_Qu8mg5v7";

npe_function(circulation)
npe_doc(ds_circulation)

npe_arg(e, int)
npe_arg(ccw, bool)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)
npe_arg(ef, Eigen::MatrixXi &)
npe_arg(ei, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::VectorXi & v_n;
  igl::circulation(e, ccw, f, e, emap, ef, ei, v_n);
  return npe::move(v_n);

npe_end_code()


