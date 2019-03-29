#include <npe.h>
#include <typedefs.h>






#include <igl/min_quad_dense_precompute.h>

const char* ds_min_quad_dense_precompute = R"igl_Qu8mg5v7(

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

 MIN_QUAD_WITH_FIXED Minimize quadratic energy Z'*A*Z + Z'*B + C
   subject to linear constraints Aeq*Z = Beq
  
   Templates:
     T  should be a eigen matrix primitive type like float or double
   Inputs:
     A  n by n matrix of quadratic coefficients
     B  n by 1 column of linear coefficients
     Aeq  m by n list of linear equality constraint coefficients
     Beq  m by 1 list of linear equality constraint constant values
     use_lu_decomposition  use lu rather than SVD
   Outputs:
     S  n by (n + m) "solve" matrix, such that S*[B', Beq'] is a solution
   Returns true on success, false on error
)igl_Qu8mg5v7";

npe_function(min_quad_dense_precompute)
npe_doc(ds_min_quad_dense_precompute)

npe_arg(a, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &)
npe_arg(aeq, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &)
npe_arg(use_lu_decomposition, bool)


npe_begin_code()

  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> & s;
  igl::min_quad_dense_precompute(a, aeq, use_lu_decomposition, s);
  return npe::move(s);

npe_end_code()


