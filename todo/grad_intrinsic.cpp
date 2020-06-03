#include <npe.h>
#include <typedefs.h>






#include <igl/grad_intrinsic.h>

const char* ds_grad_intrinsic = R"igl_Qu8mg5v7(

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

 GRAD_INTRINSIC Construct an intrinsic gradient operator.
  
   Inputs:
    l  #F by 3 list of edge lengths
    F  #F by 3 list of triangle indices into some vertex list V
   Outputs:
    G  #F*2 by #V gradient matrix: G=[Gx;Gy] where x runs along the 23 edge and
      y runs in the counter-clockwise 90° rotation.
)igl_Qu8mg5v7";

npe_function(grad_intrinsic)
npe_doc(ds_grad_intrinsic)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  Eigen::SparseMatrix<Gtype> & g;
  igl::grad_intrinsic(l, f, g);
  return npe::move(g);

npe_end_code()


