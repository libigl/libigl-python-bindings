#include <npe.h>
#include <typedefs.h>






#include <igl/writeDMAT.h>

const char* ds_write_dmat = R"igl_Qu8mg5v7(

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

 Write a matrix using ascii dmat file type
  
   Template:
     Mat  matrix type that supports .rows(), .cols(), operator(i,j)
   Inputs:
     file_name  path to .dmat file
     W  eigen matrix containing to-be-written coefficients
     ascii  write ascii file {true}
   Returns true on success, false on error
  
)igl_Qu8mg5v7";

npe_function(write_dmat)
npe_doc(ds_write_dmat)

npe_arg(file_name, std::string)
npe_arg(w, dense_float, dense_double)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writeDMAT(file_name, w, ascii);
  return ;

npe_end_code()
#include <igl/writeDMAT.h>

const char* ds_write_dmat = R"igl_Qu8mg5v7(
See writeDMAT for the documentation.
)igl_Qu8mg5v7";

npe_function(write_dmat)
npe_doc(ds_write_dmat)

npe_arg(file_name, std::string)
npe_arg(w, std::vector<std::vector<double> > &)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writeDMAT(file_name, w, ascii);
  return ;

npe_end_code()
#include <igl/writeDMAT.h>

const char* ds_write_dmat = R"igl_Qu8mg5v7(
See writeDMAT for the documentation.
)igl_Qu8mg5v7";

npe_function(write_dmat)
npe_doc(ds_write_dmat)

npe_arg(file_name, std::string)
npe_arg(w, std::vector<Scalar> &)
npe_arg(ascii, bool)


npe_begin_code()

  igl::writeDMAT(file_name, w, ascii);
  return ;

npe_end_code()


