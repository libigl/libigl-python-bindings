#include <npe.h>
#include <typedefs.h>






#include <igl/writeMESH.h>

const char* ds_write_mesh = R"igl_Qu8mg5v7(

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

 save a tetrahedral volume mesh to a .mesh file
  
   Templates:
     Scalar  type for positions and vectors (will be cast as double)
     Index  type for indices (will be cast to int)
   Input:
     mesh_file_name  path of .mesh file
     V  double matrix of vertex positions  #V by 3
     T  #T list of tet indices into vertex positions
     F  #F list of face indices into vertex positions
  
   Known bugs: Holes and regions are not supported
)igl_Qu8mg5v7";

npe_function(write_mesh)
npe_doc(ds_write_mesh)

npe_arg(mesh_file_name, std::string)
npe_arg(v, std::vector<std::vector<double> > &)
npe_arg(t, std::vector<std::vector<int> > &)
npe_arg(f, std::vector<std::vector<int> > &)


npe_begin_code()

  igl::writeMESH(mesh_file_name, v, t, f);
  return ;

npe_end_code()
#include <igl/writeMESH.h>

const char* ds_write_mesh = R"igl_Qu8mg5v7(

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

 Templates:
     DerivedV  real-value: i.e. from MatrixXd
     DerivedT  integer-value: i.e. from MatrixXi
     DerivedF  integer-value: i.e. from MatrixXi
   Input:
     mesh_file_name  path of .mesh file
     V  eigen double matrix #V by 3
     T  eigen int matrix #T by 4
     F  eigen int matrix #F by 3
)igl_Qu8mg5v7";

npe_function(write_mesh)
npe_doc(ds_write_mesh)

npe_arg(str, std::string)
npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  igl::writeMESH(str, v, t, f);
  return ;

npe_end_code()


