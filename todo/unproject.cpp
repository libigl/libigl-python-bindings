#include <npe.h>
#include <typedefs.h>
#include <igl/unproject.h>

const char* ds_unproject = R"igl_Qu8mg5v7(

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

 Eigen reimplementation of gluUnproject
  
   Inputs:
     win  #P by 3 or 3-vector (#P=1) of screen space x, y, and z coordinates
     model  4x4 model-view matrix
     proj  4x4 projection matrix
     viewport  4-long viewport vector
   Outputs:
     scene  #P by 3 or 3-vector (#P=1) the unprojected x, y, and z coordinates
)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win, dense_f32, dense_f64)
npe_arg(model, dense_f32, dense_f64)
npe_arg(proj, dense_f32, dense_f64)
npe_arg(viewport, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> scene;
  igl::unproject(win, model, proj, viewport, scene);
  return npe::move(scene);

npe_end_code()






#include <igl/unproject.h>

const char* ds_unproject = R"igl_Qu8mg5v7(
See unproject for the documentation.
)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win, Eigen::Matrix<Scalar, 3, 1> &)
npe_arg(model, Eigen::Matrix<Scalar, 4, 4> &)
npe_arg(proj, Eigen::Matrix<Scalar, 4, 4> &)
npe_arg(viewport, Eigen::Matrix<Scalar, 4, 1> &)


npe_begin_code()

  igl::unproject(win, model, proj, viewport);
  return ;

npe_end_code()


