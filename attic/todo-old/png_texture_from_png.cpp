#include <npe.h>
#include <typedefs.h>






#include <igl/texture_from_png.h>

const char* ds_texture_from_png = R"igl_Qu8mg5v7(

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

 Read an image from a .png file and use it as a texture
    
     Input:
      png_file  path to .png file
      flip  whether to flip the image vertically (A --> ∀)
     Output:
      id  of generated openGL texture
     Returns true on success, false on failure
)igl_Qu8mg5v7";

npe_function(texture_from_png)
npe_doc(ds_texture_from_png)

npe_arg(png_file, std::string)
npe_arg(flip, bool)


npe_begin_code()

  int & id;
  igl::  png::texture_from_png(png_file, flip, id);
  return npe::move(id);

npe_end_code()
#include <igl/texture_from_png.h>

const char* ds_texture_from_png = R"igl_Qu8mg5v7(
See texture_from_png for the documentation.
)igl_Qu8mg5v7";

npe_function(texture_from_png)
npe_doc(ds_texture_from_png)

npe_arg(png_file, std::string)


npe_begin_code()

  int & id;
  igl::  png::texture_from_png(png_file, id);
  return npe::move(id);

npe_end_code()
#include <igl/texture_from_png.h>

const char* ds_texture_from_png = R"igl_Qu8mg5v7(

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

 Read an image from a .png file and use it as a texture
    
     Input:
      png_file  path to .png file
     Output:
      R,G,B,A texture channels
     Returns true on success, false on failure
    
     Todo: this is an inappropriate function name. This is really just
     reading a png.... Not necessarily as a texture.
)igl_Qu8mg5v7";

npe_function(texture_from_png)
npe_doc(ds_texture_from_png)

npe_arg(png_file, std::string)


npe_begin_code()

  int & r;
  int & g;
  int & b;
  int & a;
  igl::  png::texture_from_png(png_file, r, g, b, a);
  return std::make_tuple(npe::move(r), npe::move(g), npe::move(b), npe::move(a));

npe_end_code()


