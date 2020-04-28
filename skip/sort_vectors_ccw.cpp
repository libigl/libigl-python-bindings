#include <npe.h>
#include <typedefs.h>
#include <igl/sort_vectors_ccw.h>

const char* ds_sort_vectors_ccw = R"igl_Qu8mg5v7(

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
     P               1 by 3N row vector of the vectors to be sorted, stacked horizontally
     N               #1 by 3 normal of the plane where the vectors lie
   Output:
     order           N by 1 order of the vectors (indices of the unordered vectors into
                     the ordered vector set)
     sorted          1 by 3N row vector of the ordered vectors, stacked horizontally
     inv_order       N by 1 "inverse" order of the vectors (the indices of the ordered
                     vectors into the unordered vector set)
  
)igl_Qu8mg5v7";

npe_function(sort_vectors_ccw)
npe_doc(ds_sort_vectors_ccw)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> order;
  EigenDense<npe_Scalar_> sorted;
  EigenDense<npe_Scalar_> inv_order;
  igl::sort_vectors_ccw(p, n, order, sorted, inv_order);
  return std::make_tuple(npe::move(order), npe::move(sorted), npe::move(inv_order));

npe_end_code()
#include <igl/sort_vectors_ccw.h>

const char* ds_sort_vectors_ccw = R"igl_Qu8mg5v7(
See sort_vectors_ccw for the documentation.
)igl_Qu8mg5v7";

npe_function(sort_vectors_ccw)
npe_doc(ds_sort_vectors_ccw)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> order;
  EigenDense<npe_Scalar_> sorted;
  igl::sort_vectors_ccw(p, n, order, sorted);
  return std::make_tuple(npe::move(order), npe::move(sorted));

npe_end_code()
#include <igl/sort_vectors_ccw.h>

const char* ds_sort_vectors_ccw = R"igl_Qu8mg5v7(
See sort_vectors_ccw for the documentation.
)igl_Qu8mg5v7";

npe_function(sort_vectors_ccw)
npe_doc(ds_sort_vectors_ccw)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> order;
  EigenDense<npe_Scalar_> inv_order;
  igl::sort_vectors_ccw(p, n, order, inv_order);
  return std::make_tuple(npe::move(order), npe::move(inv_order));

npe_end_code()
#include <igl/sort_vectors_ccw.h>

const char* ds_sort_vectors_ccw = R"igl_Qu8mg5v7(
See sort_vectors_ccw for the documentation.
)igl_Qu8mg5v7";

npe_function(sort_vectors_ccw)
npe_doc(ds_sort_vectors_ccw)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> order;
  igl::sort_vectors_ccw(p, n, order);
  return npe::move(order);

npe_end_code()


