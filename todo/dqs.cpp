#include <npe.h>
#include <typedefs.h>






#include <igl/dqs.h>

const char* ds_dqs = R"igl_Qu8mg5v7(

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

 Dual quaternion skinning
  
   Inputs:
     V  #V by 3 list of rest positions
     W  #W by #C list of weights
     vQ  #C list of rotation quaternions 
     vT  #C list of translation vectors
   Outputs:
     U  #V by 3 list of new positions
)igl_Qu8mg5v7";

npe_function(dqs)
npe_doc(ds_dqs)

npe_arg(v, dense_f32, dense_f64)
npe_arg(w, dense_f32, dense_f64)
npe_arg(v_q, std::vector<Q, QAlloc> &)
npe_arg(v_t, std::vector<T> &)


npe_begin_code()

  EigenDense<npe_Scalar_> u;
  igl::dqs(v, w, v_q, v_t, u);
  return npe::move(u);

npe_end_code()


