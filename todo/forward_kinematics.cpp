#include <npe.h>
#include <typedefs.h>






#include <igl/forward_kinematics.h>

const char* ds_forward_kinematics = R"igl_Qu8mg5v7(

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

 Given a skeleton and a set of relative bone rotations compute absolute
   rigid transformations for each bone.
  
   Inputs:
     C  #C by dim list of joint positions
     BE  #BE by 2 list of bone edge indices
     P  #BE list of parent indices into BE
     dQ  #BE list of relative rotations
     dT  #BE list of relative translations
   Outputs:
     vQ  #BE list of absolute rotations
     vT  #BE list of absolute translations
)igl_Qu8mg5v7";

npe_function(forward_kinematics)
npe_doc(ds_forward_kinematics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(p, Eigen::VectorXi &)
npe_arg(d_q, std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > &)
npe_arg(d_t, std::vector<Eigen::Vector3d> &)


npe_begin_code()

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > & v_q;
  std::vector<Eigen::Vector3d> & v_t;
  igl::forward_kinematics(c, be, p, d_q, d_t, v_q, v_t);
  return std::make_tuple(npe::move(v_q), npe::move(v_t));

npe_end_code()
#include <igl/forward_kinematics.h>

const char* ds_forward_kinematics = R"igl_Qu8mg5v7(

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

 Wrapper assuming each dT[i] == {0,0,0}
)igl_Qu8mg5v7";

npe_function(forward_kinematics)
npe_doc(ds_forward_kinematics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(p, Eigen::VectorXi &)
npe_arg(d_q, std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > &)


npe_begin_code()

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > & v_q;
  std::vector<Eigen::Vector3d> & v_t;
  igl::forward_kinematics(c, be, p, d_q, v_q, v_t);
  return std::make_tuple(npe::move(v_q), npe::move(v_t));

npe_end_code()
#include <igl/forward_kinematics.h>

const char* ds_forward_kinematics = R"igl_Qu8mg5v7(

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

 Outputs:
     T  #BE*(dim+1) by dim stack of transposed transformation matrices
)igl_Qu8mg5v7";

npe_function(forward_kinematics)
npe_doc(ds_forward_kinematics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(p, Eigen::VectorXi &)
npe_arg(d_q, std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > &)
npe_arg(d_t, std::vector<Eigen::Vector3d> &)


npe_begin_code()

  Eigen::MatrixXd & t;
  igl::forward_kinematics(c, be, p, d_q, d_t, t);
  return npe::move(t);

npe_end_code()
#include <igl/forward_kinematics.h>

const char* ds_forward_kinematics = R"igl_Qu8mg5v7(
See forward_kinematics for the documentation.
)igl_Qu8mg5v7";

npe_function(forward_kinematics)
npe_doc(ds_forward_kinematics)

npe_arg(c, Eigen::MatrixXd &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(p, Eigen::VectorXi &)
npe_arg(d_q, std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > &)


npe_begin_code()

  Eigen::MatrixXd & t;
  igl::forward_kinematics(c, be, p, d_q, t);
  return npe::move(t);

npe_end_code()


