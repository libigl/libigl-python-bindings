#include <npe.h>
#include <typedefs.h>






#include <igl/mosek_linprog.h>

const char* ds_mosek_linprog = R"igl_Qu8mg5v7(

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

 Solve a linear program using mosek:
     
     min c'x
     s.t. lc <= A x <= uc
          lx <= x <= ux
    
     Inputs:
       c  #x list of linear objective coefficients
       A  #A by #x matrix of linear inequality constraint coefficients
       lc  #A list of lower constraint bounds
       uc  #A list of upper constraint bounds
       lx  #x list of lower variable bounds
       ux  #x list of upper variable bounds
     Outputs:
       x  #x list of solution values
     Returns true iff success.
)igl_Qu8mg5v7";

npe_function(mosek_linprog)
npe_doc(ds_mosek_linprog)

npe_arg(c, Eigen::VectorXd &)
npe_arg(a, Eigen::SparseMatrix<double> &)
npe_arg(lc, Eigen::VectorXd &)
npe_arg(uc, Eigen::VectorXd &)
npe_arg(lx, Eigen::VectorXd &)
npe_arg(ux, Eigen::VectorXd &)


npe_begin_code()

  Eigen::VectorXd & x;
  igl::  mosek::mosek_linprog(c, a, lc, uc, lx, ux, x);
  return npe::move(x);

npe_end_code()
#include <igl/mosek_linprog.h>

const char* ds_mosek_linprog = R"igl_Qu8mg5v7(

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

 Wrapper that keeps mosek environment alive (if licence checking is
     becoming a bottleneck)
)igl_Qu8mg5v7";

npe_function(mosek_linprog)
npe_doc(ds_mosek_linprog)

npe_arg(c, Eigen::VectorXd &)
npe_arg(a, Eigen::SparseMatrix<double> &)
npe_arg(lc, Eigen::VectorXd &)
npe_arg(uc, Eigen::VectorXd &)
npe_arg(lx, Eigen::VectorXd &)
npe_arg(ux, Eigen::VectorXd &)
npe_arg(env, int &)


npe_begin_code()

  Eigen::VectorXd & x;
  igl::  mosek::mosek_linprog(c, a, lc, uc, lx, ux, env, x);
  return npe::move(x);

npe_end_code()


