#include <npe.h>
#include <typedefs.h>






#include <igl/readPNG.h>

const char* ds_read_png = R"igl_Qu8mg5v7(

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

 Read an image from a .png file into 4 memory buffers
    
     Input:
      png_file  path to .png file
     Output:
      R,G,B,A texture channels
     Returns true on success, false on failure
    
)igl_Qu8mg5v7";

npe_function(read_png)
npe_doc(ds_read_png)

npe_arg(png_file, std::string)


npe_begin_code()

  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> r;
  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> g;
  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> b;
  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> a;
  igl::  png::readPNG(png_file, r, g, b, a);
  return std::make_tuple(npe::move(r), npe::move(g), npe::move(b), npe::move(a));

npe_end_code()


