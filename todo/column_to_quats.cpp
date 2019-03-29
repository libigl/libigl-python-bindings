#include <npe.h>
#include <typedefs.h>






#include <igl/column_to_quats.h>

const char* ds_column_to_quats = R"igl_Qu8mg5v7(

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

 "Columnize" a list of quaternions (q1x,q1y,q1z,q1w,q2x,q2y,q2z,q2w,...)
  
   Inputs:
     Q  n*4-long list of coefficients
   Outputs:
     vQ  n-long list of quaternions
   Returns false if n%4!=0
)igl_Qu8mg5v7";

npe_function(column_to_quats)
npe_doc(ds_column_to_quats)

npe_arg(q, Eigen::VectorXd &)


npe_begin_code()

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > & v_q;
  igl::column_to_quats(q, v_q);
  return npe::move(v_q);

npe_end_code()


