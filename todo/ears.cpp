#include <npe.h>
#include <typedefs.h>
#include <igl/ears.h>

const char* ds_ears = R"igl_Qu8mg5v7(

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

 FIND_EARS  Find all ears (faces with two boundary edges) in a given mesh
   
   [ears,ear_opp] = find_ears(F)
  
   Inputs:
     F  #F by 3 list of triangle mesh indices
   Outputs:
     ears  #ears list of indices into F of ears
     ear_opp  #ears list of indices indicating which edge is non-boundary
       (connecting to flops)
   
)igl_Qu8mg5v7";

npe_function(ears)
npe_doc(ds_ears)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> ear;
  EigenDense<npe_Scalar_> ear_opp;
  igl::ears(f, ear, ear_opp);
  return std::make_tuple(npe::move(ear), npe::move(ear_opp));

npe_end_code()


