#include <npe.h>
#include <typedefs.h>






#include <igl/writeTGF.h>

const char* ds_write_tgf = R"igl_Qu8mg5v7(

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

 WRITETGF
  
   Write a graph to a .tgf file
  
   Input:
    filename  .tgf file name
    V  # vertices by 3 list of vertex positions
    E  # edges by 2 list of edge indices
   
   Assumes that graph vertices are 3 dimensional
)igl_Qu8mg5v7";

npe_function(write_tgf)
npe_doc(ds_write_tgf)

npe_arg(tgf_filename, std::string)
npe_arg(c, std::vector<std::vector<double> > &)
npe_arg(e, std::vector<std::vector<int> > &)


npe_begin_code()

  igl::writeTGF(tgf_filename, c, e);
  return ;

npe_end_code()
#include <igl/writeTGF.h>

const char* ds_write_tgf = R"igl_Qu8mg5v7(
See writeTGF for the documentation.
)igl_Qu8mg5v7";

npe_function(write_tgf)
npe_doc(ds_write_tgf)

npe_arg(tgf_filename, std::string)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(e, Eigen::MatrixXi &)


npe_begin_code()

  igl::writeTGF(tgf_filename, c, e);
  return ;

npe_end_code()


