#include <npe.h>
#include <typedefs.h>
#include <igl/unproject_ray.h>

const char* ds_unproject_ray = R"igl_Qu8mg5v7(

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

 Construct a ray (source point + direction vector) given a screen space
   positions (e.g. mouse) and a model-view projection constellation.
  
   Inputs:
     pos  2d screen-space position (x,y) 
     model  4x4 model-view matrix
     proj  4x4 projection matrix
     viewport  4-long viewport vector
   Outputs:
     s  source of ray (pos unprojected with z=0)
  /  dir  direction of ray (d - s) where d is pos unprojected with z=1
   
)igl_Qu8mg5v7";

npe_function(unproject_ray)
npe_doc(ds_unproject_ray)

npe_arg(pos, dense_f32, dense_f64)
npe_arg(model, dense_f32, dense_f64)
npe_arg(proj, dense_f32, dense_f64)
npe_arg(viewport, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> dir;
  igl::unproject_ray(pos, model, proj, viewport, s, dir);
  return std::make_tuple(npe::move(s), npe::move(dir));

npe_end_code()


