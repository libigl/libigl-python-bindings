#include <npe.h>
#include <typedefs.h>
#include <igl/project.h>

const char* ds_project = R"igl_Qu8mg5v7(

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
     V  #V by 3 list of object points
     model  model matrix
     proj  projection matrix
     viewport  viewport vector
   Outputs:
     P  #V by 3 list of screen space points
)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(v, dense_f32, dense_f64)
npe_arg(model, dense_f32, dense_f64)
npe_arg(proj, dense_f32, dense_f64)
npe_arg(viewport, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::project(v, model, proj, viewport, p);
  return npe::move(p);

npe_end_code()






#include <igl/project.h>

const char* ds_project = R"igl_Qu8mg5v7(

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

 Eigen reimplementation of gluProject
   Inputs:
     obj*  3D objects' x, y, and z coordinates respectively
     model  model matrix
     proj  projection matrix
     viewport  viewport vector
   Returns:
     screen space x, y, and z coordinates respectively
)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(obj, Eigen::Matrix<Scalar, 3, 1> &)
npe_arg(model, Eigen::Matrix<Scalar, 4, 4> &)
npe_arg(proj, Eigen::Matrix<Scalar, 4, 4> &)
npe_arg(viewport, Eigen::Matrix<Scalar, 4, 1> &)


npe_begin_code()

  igl::project(obj, model, proj, viewport);
  return ;

npe_end_code()


