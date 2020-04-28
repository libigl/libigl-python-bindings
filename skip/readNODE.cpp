#include <npe.h>
#include <typedefs.h>






#include <igl/readNODE.h>

const char* ds_read_node = R"igl_Qu8mg5v7(

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

 load a list of points from a .node file
  
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
     Index  type for indices (will be read as int and cast to Index)
   Input:
     node_file_name  path of .node file
   Outputs:
     V  double matrix of vertex positions  #V by dim
     I  list of indices (first tells whether 0 or 1 indexed)
)igl_Qu8mg5v7";

npe_function(read_node)
npe_doc(ds_read_node)

npe_arg(node_file_name, std::string)


npe_begin_code()

  std::vector<std::vector<double> > & v;
  std::vector<std::vector<int> > & i;
  igl::readNODE(node_file_name, v, i);
  return std::make_tuple(npe::move(v), npe::move(i));

npe_end_code()
#include <igl/readNODE.h>

const char* ds_read_node = R"igl_Qu8mg5v7(

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

 Input:
     node_file_name  path of .node file
   Outputs:
     V  eigen double matrix #V by dim
)igl_Qu8mg5v7";

npe_function(read_node)
npe_doc(ds_read_node)

npe_arg(node_file_name, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> i;
  igl::readNODE(node_file_name, v, i);
  return std::make_tuple(npe::move(v), npe::move(i));

npe_end_code()


