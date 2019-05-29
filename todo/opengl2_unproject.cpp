#include <npe.h>
#include <typedefs.h>
#include <igl/unproject.h>

const char* ds_unproject = R"igl_Qu8mg5v7(
See unproject for the documentation.
)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> obj;
  igl::  opengl2::unproject(win, obj);
  return npe::move(obj);

npe_end_code()
#include <igl/unproject.h>

const char* ds_unproject = R"igl_Qu8mg5v7(
See unproject for the documentation.
)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win, dense_float, dense_double)


npe_begin_code()

  igl::  opengl2::unproject(win);
  return ;

npe_end_code()






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

 Wrapper for gluUnproject that uses the current GL_MODELVIEW_MATRIX,
     GL_PROJECTION_MATRIX, and GL_VIEWPORT
     Inputs:
       win*  screen space x, y, and z coordinates respectively
     Outputs:
       obj*  pointers to 3D objects' x, y, and z coordinates respectively
     Returns return value of gluUnProject call
)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win_x, double)
npe_arg(win_y, double)
npe_arg(win_z, double)


npe_begin_code()

  double * obj_x;
  double * obj_y;
  double * obj_z;
  igl::  opengl2::unproject(win_x, win_y, win_z, obj_x, obj_y, obj_z);
  return std::make_tuple(npe::move(obj_x), npe::move(obj_y), npe::move(obj_z));

npe_end_code()


