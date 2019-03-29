#include <npe.h>
#include <typedefs.h>






#include <igl/readMESH.h>

const char* ds_read_mesh = R"igl_Qu8mg5v7(

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

 load a tetrahedral volume mesh from a .mesh file
  
   Templates:
     Scalar  type for positions and vectors (will be read as double and cast
       to Scalar)
     Index  type for indices (will be read as int and cast to Index)
   Input:
     mesh_file_name  path of .mesh file
   Outputs:
     V  double matrix of vertex positions  #V by 3
     T  #T list of tet indices into vertex positions
     F  #F list of face indices into vertex positions
  
   Known bugs: Holes and regions are not supported
)igl_Qu8mg5v7";

npe_function(read_mesh)
npe_doc(ds_read_mesh)

npe_arg(mesh_file_name, std::string)


npe_begin_code()

  std::vector<std::vector<double> > & v;
  std::vector<std::vector<int> > & t;
  std::vector<std::vector<int> > & f;
  igl::readMESH(mesh_file_name, v, t, f);
  return std::make_tuple(npe::move(v), npe::move(t), npe::move(f));

npe_end_code()
#include <igl/readMESH.h>

const char* ds_read_mesh = R"igl_Qu8mg5v7(

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
     mesh_file  pointer to already opened .mesh file 
   Outputs:
     mesh_file  closed file
)igl_Qu8mg5v7";

npe_function(read_mesh)
npe_doc(ds_read_mesh)



npe_begin_code()

  FILE * mesh_file;
  std::vector<std::vector<double> > & v;
  std::vector<std::vector<int> > & t;
  std::vector<std::vector<int> > & f;
  igl::readMESH(mesh_file, v, t, f);
  return std::make_tuple(npe::move(mesh_file), npe::move(v), npe::move(t), npe::move(f));

npe_end_code()
#include <igl/readMESH.h>

const char* ds_read_mesh = R"igl_Qu8mg5v7(

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
     mesh_file_name  path of .mesh file
   Outputs:
     V  eigen double matrix #V by 3
     T  eigen int matrix #T by 4
     F  eigen int matrix #F by 3
)igl_Qu8mg5v7";

npe_function(read_mesh)
npe_doc(ds_read_mesh)

npe_arg(mesh_file_name, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> t;
  EigenDense<npe_Scalar_> f;
  igl::readMESH(mesh_file_name, v, t, f);
  return std::make_tuple(npe::move(v), npe::move(t), npe::move(f));

npe_end_code()
#include <igl/readMESH.h>

const char* ds_read_mesh = R"igl_Qu8mg5v7(

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
     mesh_file  pointer to already opened .mesh file 
   Outputs:
     mesh_file  closed file
)igl_Qu8mg5v7";

npe_function(read_mesh)
npe_doc(ds_read_mesh)



npe_begin_code()

  FILE * mesh_file;
  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> t;
  EigenDense<npe_Scalar_> f;
  igl::readMESH(mesh_file, v, t, f);
  return std::make_tuple(npe::move(mesh_file), npe::move(v), npe::move(t), npe::move(f));

npe_end_code()


