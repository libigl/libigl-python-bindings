#include <npe.h>
#include <typedefs.h>






#include <igl/progressive_hulls.h>

const char* ds_progressive_hulls = R"igl_Qu8mg5v7(

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

 Assumes (V,F) is a closed manifold mesh 
     Collapses edges until desired number of faces is achieved but ensures
     that new vertices are placed outside all previous meshes as per
     "progressive hulls" in "Silhouette clipping" [Sander et al. 2000].
    
     Inputs:
       V  #V by dim list of vertex positions
       F  #F by 3 list of face indices into V.
       max_m  desired number of output faces
     Outputs:
       U  #U by dim list of output vertex posistions (can be same ref as V)
       G  #G by 3 list of output face indices into U (can be same ref as G)
       J  #G list of indices into F of birth faces
     Returns true if m was reached (otherwise #G > m)
)igl_Qu8mg5v7";

npe_function(progressive_hulls)
npe_doc(ds_progressive_hulls)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(max_m, size_t)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  igl::  copyleft::progressive_hulls(v, f, max_m, u, g, j);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j));

npe_end_code()


