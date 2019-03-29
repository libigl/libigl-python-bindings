#include <npe.h>
#include <typedefs.h>






#include <igl/texture_from_file.h>

const char* ds_texture_from_file = R"igl_Qu8mg5v7(

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

 Read an image from an image file and use it as a texture. Officially,
     only <del>.tga and</del> .png are supported. Any filetype read by
     ImageMagick's `convert` will work via an unsafe system call.
    
     Input:
      filename  path to image file
     Output:
      id  of generated openGL texture
     Returns true on success, false on failure
)igl_Qu8mg5v7";

npe_function(texture_from_file)
npe_doc(ds_texture_from_file)

npe_arg(filename, std::string)


npe_begin_code()

  int & id;
  igl::  png::texture_from_file(filename, id);
  return npe::move(id);

npe_end_code()


