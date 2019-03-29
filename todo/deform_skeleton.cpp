#include <npe.h>
#include <typedefs.h>






#include <igl/deform_skeleton.h>

const char* ds_deform_skeleton = R"igl_Qu8mg5v7(

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

 Deform a skeleton.
  
   Inputs:
     C  #C by 3 list of joint positions
     BE  #BE by 2 list of bone edge indices
     vA  #BE list of bone transformations
   Outputs
     CT  #BE*2 by 3 list of deformed joint positions
     BET  #BE by 2 list of bone edge indices (maintains order)
  
)igl_Qu8mg5v7";

npe_function(deform_skeleton)
npe_doc(ds_deform_skeleton)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(v_a, std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > &)


npe_begin_code()

  Eigen::MatrixXd & ct;
  Eigen::MatrixXi & bet;
  igl::deform_skeleton(c, be, v_a, ct, bet);
  return std::make_tuple(npe::move(ct), npe::move(bet));

npe_end_code()
#include <igl/deform_skeleton.h>

const char* ds_deform_skeleton = R"igl_Qu8mg5v7(

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
     T  #BE*4 by 3 list of stacked transformation matrix
)igl_Qu8mg5v7";

npe_function(deform_skeleton)
npe_doc(ds_deform_skeleton)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(t, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::MatrixXd & ct;
  Eigen::MatrixXi & bet;
  igl::deform_skeleton(c, be, t, ct, bet);
  return std::make_tuple(npe::move(ct), npe::move(bet));

npe_end_code()


