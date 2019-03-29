#include <npe.h>
#include <typedefs.h>






#include <igl/readWRL.h>

const char* ds_read_wrl = R"igl_Qu8mg5v7(

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

 Read a mesh from an ascii wrl file, filling in vertex positions and face
   indices of the first model. Mesh may have faces of any number of degree
  
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
     Index  type for indices (will be read as int and cast to Index)
   Inputs:
    str  path to .wrl file
   Outputs:
     V  double matrix of vertex positions  #V by 3
     F  #F list of face indices into vertex positions
   Returns true on success, false on errors
)igl_Qu8mg5v7";

npe_function(read_wrl)
npe_doc(ds_read_wrl)

npe_arg(wrl_file_name, std::string)


npe_begin_code()

  std::vector<std::vector<double> > & v;
  std::vector<std::vector<int> > & f;
  igl::readWRL(wrl_file_name, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()
#include <igl/readWRL.h>

const char* ds_read_wrl = R"igl_Qu8mg5v7(

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

 Inputs:
     wrl_file  pointer to already opened .wrl file 
   Outputs:
     wrl_file  closed file
)igl_Qu8mg5v7";

npe_function(read_wrl)
npe_doc(ds_read_wrl)



npe_begin_code()

  FILE * wrl_file;
  std::vector<std::vector<double> > & v;
  std::vector<std::vector<int> > & f;
  igl::readWRL(wrl_file, v, f);
  return std::make_tuple(npe::move(wrl_file), npe::move(v), npe::move(f));

npe_end_code()


