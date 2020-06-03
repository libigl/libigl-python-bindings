#include <npe.h>
#include <typedefs.h>






#include <igl/miq.h>

const char* ds_miq = R"igl_Qu8mg5v7(

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

 Inputs:
       V              #V by 3 list of mesh vertex 3D positions
       F              #F by 3 list of faces indices in V
       PD1            #V by 3 first line of the Jacobian per triangle
       PD2            #V by 3 second line of the Jacobian per triangle
                      (optional, if empty it will be a vector in the tangent plane orthogonal to PD1)
       scale          global scaling for the gradient (controls the quads resolution)
       stiffness      weight for the stiffness iterations
       direct_round   greedily round all integer variables at once (greatly improves optimization speed but lowers quality)
       iter           stiffness iterations (0 = no stiffness)
       local_iter     number of local iterations for the integer rounding
       do_round       enables the integer rounding (disabling it could be useful for debugging)
       round_vertices id of additional vertices that should be snapped to integer coordinates
       hard_features  #H by 2 list of pairs of vertices that belongs to edges that should be snapped to integer coordinates
    
     Output:
       UV             #UV by 2 list of vertices in 2D
       FUV            #FUV by 3 list of face indices in UV
    
     TODO: rename the parameters name in the cpp consistently
           improve the handling of hard_features, right now it might fail in difficult cases
)igl_Qu8mg5v7";

npe_function(miq)
npe_doc(ds_miq)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1, dense_float, dense_double)
npe_arg(pd2, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> uv;
  EigenDense<npe_Scalar_> fuv;
  double scale;
  double stiffness;
  bool direct_round;
  int iter;
  int local_iter;
  bool do_round;
  bool singularity_round;
  std::vector<int> round_vertices;
  std::vector<std::vector<int> > hard_features;
  igl::  copyleft::  comiso::miq(v, f, pd1, pd2, uv, fuv, scale, stiffness, direct_round, iter, local_iter, do_round, singularity_round, round_vertices, hard_features);
  return std::make_tuple(npe::move(uv), npe::move(fuv), npe::move(scale), npe::move(stiffness), npe::move(direct_round), npe::move(iter), npe::move(local_iter), npe::move(do_round), npe::move(singularity_round), npe::move(round_vertices), npe::move(hard_features));

npe_end_code()
#include <igl/miq.h>

const char* ds_miq = R"igl_Qu8mg5v7(

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

 Helper function that allows to directly provided pre-combed bisectors for an already cut mesh
     Additional input:
     PD1_combed, PD2_combed  :   #F by 3 combed jacobian
     BIS1_combed, BIS2_combed:   #F by 3 pre combed bi-sectors
     MMatch:                     #F by 3 list of per-corner integer PI/2 rotations
     Singular:                   #V list of flag that denotes if a vertex is singular or not
     SingularDegree:             #V list of flag that denotes the degree of the singularity
     Seams:                      #F by 3 list of per-corner flag that denotes seams
)igl_Qu8mg5v7";

npe_function(miq)
npe_doc(ds_miq)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1_combed, dense_float, dense_double)
npe_arg(pd2_combed, dense_float, dense_double)
npe_arg(m_match, Eigen::Matrix<int, Eigen::Dynamic, 3> &)
npe_arg(singular, Eigen::Matrix<int, Eigen::Dynamic, 1> &)
npe_arg(seams, Eigen::Matrix<int, Eigen::Dynamic, 3> &)


npe_begin_code()

  EigenDense<npe_Scalar_> uv;
  EigenDense<npe_Scalar_> fuv;
  double gradient_size;
  double stiffness;
  bool direct_round;
  int iter;
  int local_iter;
  bool do_round;
  bool singularity_round;
  std::vector<int> round_vertices;
  std::vector<std::vector<int> > hard_features;
  igl::  copyleft::  comiso::miq(v, f, pd1_combed, pd2_combed, m_match, singular, seams, uv, fuv, gradient_size, stiffness, direct_round, iter, local_iter, do_round, singularity_round, round_vertices, hard_features);
  return std::make_tuple(npe::move(uv), npe::move(fuv), npe::move(gradient_size), npe::move(stiffness), npe::move(direct_round), npe::move(iter), npe::move(local_iter), npe::move(do_round), npe::move(singularity_round), npe::move(round_vertices), npe::move(hard_features));

npe_end_code()


