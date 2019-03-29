#include <npe.h>
#include <typedefs.h>






#include <igl/file_contents_as_string.h>

const char* ds_file_contents_as_string = R"igl_Qu8mg5v7(

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

 Read a files contents as plain text into a given string
   Inputs:
     file_name  path to file to be read
   Outputs:
     content  output string containing contents of the given file
   Returns true on succes, false on error
)igl_Qu8mg5v7";

npe_function(file_contents_as_string)
npe_doc(ds_file_contents_as_string)

npe_arg(file_name, std::string)


npe_begin_code()

  std::string & content;
  igl::file_contents_as_string(file_name, content);
  return npe::move(content);

npe_end_code()
#include <igl/file_contents_as_string.h>

const char* ds_file_contents_as_string = R"igl_Qu8mg5v7(
See file_contents_as_string for the documentation.
)igl_Qu8mg5v7";

npe_function(file_contents_as_string)
npe_doc(ds_file_contents_as_string)

npe_arg(file_name, std::string)


npe_begin_code()

  igl::file_contents_as_string(file_name);
  return ;

npe_end_code()


