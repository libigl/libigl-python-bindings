#include <npe.h>
#include <typedefs.h>






#include <igl/read_into_tetgenio.h>

const char* ds_read_into_tetgenio = R"igl_Qu8mg5v7(

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

 Read a mesh or point set into tetgenio (input object for calling
       tetgen).  Many file formats are already supported by tetgen:
         .off
         .ply
         .node
         .ply
         .medit
         .vtk
         etc.
       Notably it does not support .obj which is loaded by hand here (also
       demonstrating how to load points/faces programmatically)
      
       If the file extension is not recognized the filename is assumed to be
       the basename of a collection describe a tetmesh, (of which at least
       the .node file must exist):
         [filename].node
         [filename].ele
         [filename].face
         [filename].edge
         [filename].vol
      
       Inputs:
         path  path to file or basename to files
       Outputs:
         in  tetgenio input object
       Returns true on success, false on error
)igl_Qu8mg5v7";

npe_function(read_into_tetgenio)
npe_doc(ds_read_into_tetgenio)

npe_arg(path, std::string &)


npe_begin_code()

  int & in;
  igl::  copyleft::  tetgen::read_into_tetgenio(path, in);
  return npe::move(in);

npe_end_code()


