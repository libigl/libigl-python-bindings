#include <npe.h>
#include <typedefs.h>
#include <igl/unique_simplices.h>

const char* ds_unique_simplices = R"igl_Qu8mg5v7(

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

 Find *combinatorially* unique simplices in F.  **Order independent**
  
   Inputs:
     F  #F by simplex-size list of simplices
   Outputs:
     FF  #FF by simplex-size list of unique simplices in F
     IA  #FF index vector so that FF == sort(F(IA,:),2);
     IC  #F index vector so that sort(F,2) == FF(IC,:);
)igl_Qu8mg5v7";

npe_function(unique_simplices)
npe_doc(ds_unique_simplices)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> ia;
  EigenDense<npe_Scalar_> ic;
  igl::unique_simplices(f, ff, ia, ic);
  return std::make_tuple(npe::move(ff), npe::move(ia), npe::move(ic));

npe_end_code()
#include <igl/unique_simplices.h>

const char* ds_unique_simplices = R"igl_Qu8mg5v7(
See unique_simplices for the documentation.
)igl_Qu8mg5v7";

npe_function(unique_simplices)
npe_doc(ds_unique_simplices)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  igl::unique_simplices(f, ff);
  return npe::move(ff);

npe_end_code()


