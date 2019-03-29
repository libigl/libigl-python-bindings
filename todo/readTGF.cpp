#include <npe.h>
#include <typedefs.h>






#include <igl/readTGF.h>

const char* ds_read_tgf = R"igl_Qu8mg5v7(

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

 READTGF
  
   [V,E,P,BE,CE,PE] = readTGF(filename)
  
   Read a graph from a .tgf file
  
   Input:
    filename  .tgf file name
   Output:
    V  # vertices by 3 list of vertex positions
    E  # edges by 2 list of edge indices
    P  # point-handles list of point handle indices
    BE # bone-edges by 2 list of bone-edge indices
    CE # cage-edges by 2 list of cage-edge indices
    PE # pseudo-edges by 2 list of pseudo-edge indices
   
   Assumes that graph vertices are 3 dimensional
)igl_Qu8mg5v7";

npe_function(read_tgf)
npe_doc(ds_read_tgf)

npe_arg(tgf_filename, std::string)


npe_begin_code()

  std::vector<std::vector<double> > & c;
  std::vector<std::vector<int> > & e;
  std::vector<int> & p;
  std::vector<std::vector<int> > & be;
  std::vector<std::vector<int> > & ce;
  std::vector<std::vector<int> > & pe;
  igl::readTGF(tgf_filename, c, e, p, be, ce, pe);
  return std::make_tuple(npe::move(c), npe::move(e), npe::move(p), npe::move(be), npe::move(ce), npe::move(pe));

npe_end_code()
#include <igl/readTGF.h>

const char* ds_read_tgf = R"igl_Qu8mg5v7(
See readTGF for the documentation.
)igl_Qu8mg5v7";

npe_function(read_tgf)
npe_doc(ds_read_tgf)

npe_arg(tgf_filename, std::string)


npe_begin_code()

  Eigen::MatrixXd & c;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & p;
  Eigen::MatrixXi & be;
  Eigen::MatrixXi & ce;
  Eigen::MatrixXi & pe;
  igl::readTGF(tgf_filename, c, e, p, be, ce, pe);
  return std::make_tuple(npe::move(c), npe::move(e), npe::move(p), npe::move(be), npe::move(ce), npe::move(pe));

npe_end_code()
#include <igl/readTGF.h>

const char* ds_read_tgf = R"igl_Qu8mg5v7(
See readTGF for the documentation.
)igl_Qu8mg5v7";

npe_function(read_tgf)
npe_doc(ds_read_tgf)

npe_arg(tgf_filename, std::string)


npe_begin_code()

  Eigen::MatrixXd & c;
  Eigen::MatrixXi & e;
  igl::readTGF(tgf_filename, c, e);
  return std::make_tuple(npe::move(c), npe::move(e));

npe_end_code()


