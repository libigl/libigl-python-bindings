#include <npe.h>
#include <typedefs.h>






#include <igl/qslim.h>

const char* ds_qslim = R"igl_Qu8mg5v7(

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

 Decimate (simplify) a triangle mesh in nD according to the paper
   "Simplifying Surfaces with Color and Texture using Quadric Error Metrics"
   by [Garland and Heckbert, 1987] (technically a followup to qslim). The
   mesh can have open boundaries but should be edge-manifold.
  
   Inputs:
     V  #V by dim list of vertex positions. Assumes that vertices w
     F  #F by 3 list of triangle indices into V
     max_m  desired number of output faces
   Outputs:
     U  #U by dim list of output vertex posistions (can be same ref as V)
     G  #G by 3 list of output face indices into U (can be same ref as G)
     J  #G list of indices into F of birth face
     I  #U list of indices into V of birth vertices
)igl_Qu8mg5v7";

npe_function(qslim)
npe_doc(ds_qslim)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(max_m, size_t)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  Eigen::VectorXi & i;
  igl::qslim(v, f, max_m, u, g, j, i);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()


