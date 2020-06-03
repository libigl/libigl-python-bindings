#include <npe.h>
#include <typedefs.h>
#include <igl/unproject_on_plane.h>

const char* ds_unproject_on_plane = R"igl_Qu8mg5v7(

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
   so that it lies on given plane.
  
   Inputs:
     UV  2-long uv-coordinates of screen space point
     M  4 by 4 projection matrix
     VP  4-long viewport: (corner_u, corner_v, width, height)
     P  4-long plane equation coefficients: P*(X 1) = 0
   Outputs:
     Z  3-long world coordinate
)igl_Qu8mg5v7";

npe_function(unproject_on_plane)
npe_doc(ds_unproject_on_plane)

npe_arg(uv, dense_f32, dense_f64)
npe_arg(m, dense_f32, dense_f64)
npe_arg(vp, dense_f32, dense_f64)
npe_arg(p, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> z;
  igl::unproject_on_plane(uv, m, vp, p, z);
  return npe::move(z);

npe_end_code()


