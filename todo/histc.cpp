#include <npe.h>
#include <typedefs.h>
#include <igl/histc.h>

const char* ds_histc = R"igl_Qu8mg5v7(

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

 Like matlab's histc. Count occurrences of values in X between consecutive
   entries in E
  
   Inputs:
     X  m-long Vector of values
     E  n-long Monotonically increasing vector of edges
   Outputs:
     N  n-long vector where N(k) reveals how many values in X fall between
       E(k) <= X < E(k+1)
     B  m-long vector of bin ids so that B(j) = k if E(k) <= X(j) < E(k+1).
       B(j) = -1 if X(j) is outside of E.
  
   O(n+m*log(n))
)igl_Qu8mg5v7";

npe_function(histc)
npe_doc(ds_histc)

npe_arg(x, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> n;
  EigenDense<npe_Scalar_> b;
  igl::histc(x, e, n, b);
  return std::make_tuple(npe::move(n), npe::move(b));

npe_end_code()
#include <igl/histc.h>

const char* ds_histc = R"igl_Qu8mg5v7(

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

 Truly O(m*log(n))
)igl_Qu8mg5v7";

npe_function(histc)
npe_doc(ds_histc)

npe_arg(x, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> b;
  igl::histc(x, e, b);
  return npe::move(b);

npe_end_code()






#include <igl/histc.h>

const char* ds_histc = R"igl_Qu8mg5v7(

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

 Scalar search wrapper
)igl_Qu8mg5v7";

npe_function(histc)
npe_doc(ds_histc)

npe_arg(x, typename DerivedE::Scalar &)
npe_arg(e, dense_float, dense_double)


npe_begin_code()

  typename DerivedE::Index & b;
  igl::histc(x, e, b);
  return npe::move(b);

npe_end_code()


