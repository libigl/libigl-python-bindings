#include <npe.h>
#include <typedefs.h>
#include <igl/unproject_on_line.h>

const char* ds_unproject_on_line = R"igl_Qu8mg5v7(

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

   Z  3d position of closest point on line to viewing ray through UV
)igl_Qu8mg5v7";

npe_function(unproject_on_line)
npe_doc(ds_unproject_on_line)

npe_arg(uv, dense_f32, dense_f64)
npe_arg(m, dense_f32, dense_f64)
npe_arg(vp, dense_f32, dense_f64)
npe_arg(origin, dense_f32, dense_f64)
npe_arg(dir, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> z;
  igl::unproject_on_line(uv, m, vp, origin, dir, z);
  return npe::move(z);

npe_end_code()






#include <igl/unproject_on_line.h>

const char* ds_unproject_on_line = R"igl_Qu8mg5v7(

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

 Given a screen space point (u,v) and the current projection matrix (e.g.
   gl_proj * gl_modelview) and viewport, _unproject_ the point into the scene
   so that it lies on given line (origin and dir) and projects as closely as
   possible to the given screen space point.
  
   Inputs:
     UV  2-long uv-coordinates of screen space point
     M  4 by 4 projection matrix
     VP  4-long viewport: (corner_u, corner_v, width, height)
     origin  point on line
     dir  vector parallel to line
   Output:
     t  line parameter so that closest poin on line to viewer ray through UV
       lies at origin+t*dir
)igl_Qu8mg5v7";

npe_function(unproject_on_line)
npe_doc(ds_unproject_on_line)

npe_arg(uv, dense_f32, dense_f64)
npe_arg(m, dense_f32, dense_f64)
npe_arg(vp, dense_f32, dense_f64)
npe_arg(origin, dense_f32, dense_f64)
npe_arg(dir, dense_f32, dense_f64)


npe_begin_code()

  typename DerivedUV::Scalar & t;
  igl::unproject_on_line(uv, m, vp, origin, dir, t);
  return npe::move(t);

npe_end_code()


