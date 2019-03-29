#include <npe.h>
#include <typedefs.h>






#include <igl/ramer_douglas_peucker.h>

const char* ds_ramer_douglas_peucker = R"igl_Qu8mg5v7(

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

 Ramer-Douglas-Peucker piecewise-linear curve simplification.
  
   Inputs:
     P  #P by dim ordered list of vertices along the curve
     tol  tolerance (maximal euclidean distance allowed between the new line
       and a vertex)
   Outputs:
     S  #S by dim ordered list of points along the curve
     J  #S list of indices into P so that S = P(J,:)
)igl_Qu8mg5v7";

npe_function(ramer_douglas_peucker)
npe_doc(ds_ramer_douglas_peucker)

npe_arg(p, dense_f32, dense_f64)
npe_arg(tol, typename DerivedP::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> j;
  igl::ramer_douglas_peucker(p, tol, s, j);
  return std::make_tuple(npe::move(s), npe::move(j));

npe_end_code()
#include <igl/ramer_douglas_peucker.h>

const char* ds_ramer_douglas_peucker = R"igl_Qu8mg5v7(

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

 Run (Ramer-)Duglass-Peucker curve simplification but keep track of where
   every point on the original curve maps to on the simplified curve.
  
   Inputs:
     P  #P by dim list of points, (use P([1:end 1],:) for loops)
     tol  DP tolerance
   Outputs:
     S  #S by dim list of points along simplified curve
     J  #S indices into P of simplified points
     Q  #P by dim list of points mapping along simplified curve
  
)igl_Qu8mg5v7";

npe_function(ramer_douglas_peucker)
npe_doc(ds_ramer_douglas_peucker)

npe_arg(p, dense_f32, dense_f64)
npe_arg(tol, typename DerivedP::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> q;
  igl::ramer_douglas_peucker(p, tol, s, j, q);
  return std::make_tuple(npe::move(s), npe::move(j), npe::move(q));

npe_end_code()


