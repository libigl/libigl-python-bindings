#include <npe.h>
#include <typedefs.h>






#include <igl/random_search.h>

const char* ds_random_search = R"igl_Qu8mg5v7(

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

 Solve the problem:
  
     minimize f(x)
     subject to lb ≤ x ≤ ub 
   
   by uniform random search.
  
   Inputs:
     f  function to minimize
     LB  #X vector of finite lower bounds
     UB  #X vector of finite upper bounds
     iters  number of iterations
   Outputs:
     X  #X optimal parameter vector
   Returns f(X)
  
)igl_Qu8mg5v7";

npe_function(random_search)
npe_doc(ds_random_search)

npe_arg(f, std::function<Scalar (DerivedX &)>)
npe_arg(lb, dense_f32, dense_f64)
npe_arg(ub, dense_f32, dense_f64)
npe_arg(iters, int)


npe_begin_code()

  DerivedX & x;
  igl::random_search(f, lb, ub, iters, x);
  return npe::move(x);

npe_end_code()


