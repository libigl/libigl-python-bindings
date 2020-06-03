#include <npe.h>
#include <typedefs.h>
#include <igl/model_proj_viewport.h>

const char* ds_model_proj_viewport = R"igl_Qu8mg5v7(

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

 Collect the model-view, projection and viewport matrices
    
     Outputs:
       model  4x4 modelview matrix
       proj   4x4 projection matrix
       viewport  4x1 viewport vector
    
)igl_Qu8mg5v7";

npe_function(model_proj_viewport)
npe_doc(ds_model_proj_viewport)



npe_begin_code()

  EigenDense<npe_Scalar_> model;
  EigenDense<npe_Scalar_> proj;
  EigenDense<npe_Scalar_> viewport;
  igl::  opengl2::model_proj_viewport(model, proj, viewport);
  return std::make_tuple(npe::move(model), npe::move(proj), npe::move(viewport));

npe_end_code()


