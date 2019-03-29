#include <npe.h>
#include <typedefs.h>






#include <igl/boundary_conditions.h>

const char* ds_boundary_conditions = R"igl_Qu8mg5v7(

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

 Compute boundary conditions for automatic weights computation. This
   function expects that the given mesh (V,Ele) has sufficient samples
   (vertices) exactly at point handle locations and exactly along bone and
   cage edges.
  
   Inputs:
     V  #V by dim list of domain vertices
     Ele  #Ele by simplex-size list of simplex indices
     C  #C by dim list of handle positions
     P  #P by 1 list of point handle indices into C
     BE  #BE by 2 list of bone edge indices into C
     CE  #CE by 2 list of cage edge indices into *P*
   Outputs:
     b  #b list of boundary indices (indices into V of vertices which have
       known, fixed values)
     bc #b by #weights list of known/fixed values for boundary vertices
       (notice the #b != #weights in general because #b will include all the
       intermediary samples along each bone, etc.. The ordering of the
       weights corresponds to [P;BE]
   Returns false if boundary conditions are suspicious:
     P and BE are empty
     bc is empty
     some column of bc doesn't have a 0 (assuming bc has >1 columns)
     some column of bc doesn't have a 1 (assuming bc has >1 columns)
)igl_Qu8mg5v7";

npe_function(boundary_conditions)
npe_doc(ds_boundary_conditions)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(ele, Eigen::MatrixXi &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(p, Eigen::VectorXi &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(ce, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::VectorXi & b;
  Eigen::MatrixXd & bc;
  igl::boundary_conditions(v, ele, c, p, be, ce, b, bc);
  return std::make_tuple(npe::move(b), npe::move(bc));

npe_end_code()


