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

 Eigen wrapper
)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(obj, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> win;
  igl::  opengl2::project(obj, win);
  return npe::move(win);

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

 Eigen wrapper  with return
)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(obj, dense_float, dense_double)


npe_begin_code()

  igl::  opengl2::project(obj);
  return ;

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

 Wrapper for gluProject that uses the current GL_MODELVIEW_MATRIX,
     GL_PROJECTION_MATRIX, and GL_VIEWPORT
     Inputs:
       obj*  3D objects' x, y, and z coordinates respectively
     Outputs:
       win*  pointers to screen space x, y, and z coordinates respectively
     Returns return value of gluProject call
)igl_Qu8mg5v7";

npe_function(project)
npe_doc(ds_project)

npe_arg(obj_x, double)
npe_arg(obj_y, double)
npe_arg(obj_z, double)


npe_begin_code()

  double * win_x;
  double * win_y;
  double * win_z;
  igl::  opengl2::project(obj_x, obj_y, obj_z, win_x, win_y, win_z);
  return std::make_tuple(npe::move(win_x), npe::move(win_y), npe::move(win_z));

npe_end_code()


