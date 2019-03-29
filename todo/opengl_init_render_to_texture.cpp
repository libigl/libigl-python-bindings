#include <npe.h>
#include <typedefs.h>






#include <igl/init_render_to_texture.h>

const char* ds_init_render_to_texture = R"igl_Qu8mg5v7(

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

 Create a frame buffer that renders color to a RGBA texture a depth to a
     "render buffer".
    
     After calling this, you can use with something like:
    
         glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
         if(!depth_texture)
         {
           glBindRenderbuffer(GL_RENDERBUFFER, d_id);
         }
         
          draw scene ...
         
          clean up
         glBindFramebuffer(GL_FRAMEBUFFER,0);
         if(!depth_texture)
         {
           glBindRenderbuffer(GL_RENDERBUFFER, 0);
         }
          Later ...
         glActiveTexture(GL_TEXTURE0+0);
         glBindTexture(GL_TEXTURE_2D,tex_id);
         if(depth_texture)
         {
           glActiveTexture(GL_TEXTURE0+1);
           glBindTexture(GL_TEXTURE_2D,d_id);
         }
          draw textures
          
         
    
     Inputs:
       width  image width
       height  image height
       depth_texture  whether to create a texture for depth or to create a
         render buffer for depth 
     Outputs:
       tex_id  id of the texture
       fbo_id  id of the frame buffer object
       d_id  id of the depth texture or frame buffer object
    
)igl_Qu8mg5v7";

npe_function(init_render_to_texture)
npe_doc(ds_init_render_to_texture)

npe_arg(width, size_t)
npe_arg(height, size_t)
npe_arg(depth_texture, bool)


npe_begin_code()

  int & tex_id;
  int & fbo_id;
  int & d_id;
  igl::  opengl::init_render_to_texture(width, height, depth_texture, tex_id, fbo_id, d_id);
  return std::make_tuple(npe::move(tex_id), npe::move(fbo_id), npe::move(d_id));

npe_end_code()
#include <igl/init_render_to_texture.h>

const char* ds_init_render_to_texture = R"igl_Qu8mg5v7(

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

 Wrapper with depth_texture = false for legacy reasons
)igl_Qu8mg5v7";

npe_function(init_render_to_texture)
npe_doc(ds_init_render_to_texture)

npe_arg(width, size_t)
npe_arg(height, size_t)


npe_begin_code()

  int & tex_id;
  int & fbo_id;
  int & dfbo_id;
  igl::  opengl::init_render_to_texture(width, height, tex_id, fbo_id, dfbo_id);
  return std::make_tuple(npe::move(tex_id), npe::move(fbo_id), npe::move(dfbo_id));

npe_end_code()


