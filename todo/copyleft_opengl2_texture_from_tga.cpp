#include <npe.h>
#include <typedefs.h>






#include <igl/texture_from_tga.h>

const char* ds_texture_from_tga = R"igl_Qu8mg5v7(

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

 Read an image from a .tga file and use it as a texture
    
     Input:
      tga_file  path to .tga file
     Output:
      id  of generated openGL texture
     Returns true on success, false on failure
)igl_Qu8mg5v7";

npe_function(texture_from_tga)
npe_doc(ds_texture_from_tga)

npe_arg(tga_file, std::string)


npe_begin_code()

  GLuint & id;
  igl::  opengl::texture_from_tga(tga_file, id);
  return npe::move(id);

npe_end_code()


