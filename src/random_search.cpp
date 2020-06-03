#include <npe.h>
#include <typedefs.h>

#include <pybind11/stl.h>



#include <igl/random_search.h>

const char *ds_random_search = R"igl_Qu8mg5v7(

 Solve the problem:

     minimize f(x)
     subject to lb ≤ x ≤ ub

   by uniform random search.

Parameters
----------
f  function to minimize
LB  #X vector of finite lower bounds
UB  #X vector of finite upper bounds
iters  number of iterations

Returns
-------
X  #X optimal parameter vector
Returns f(X)

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(random_search)
npe_doc(ds_random_search)

npe_arg(f, const std::function< typename EigenDenseFloat::Scalar (Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> &) >)
npe_arg(lb, EigenDenseFloat)
npe_arg(ub, EigenDenseFloat)
npe_arg(iters, int)


npe_begin_code()

  Eigen::Matrix<typename EigenDenseFloat::Scalar, Eigen::Dynamic, 1> x;
  const auto obj = igl::random_search(f, lb, ub, iters, x);
  return std::make_tuple(obj, npe::move(x));

npe_end_code()

