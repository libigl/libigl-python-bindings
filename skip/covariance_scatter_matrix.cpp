#include <npe.h>
#include <typedefs.h>






#include <igl/covariance_scatter_matrix.h>

const char* ds_covariance_scatter_matrix = R"igl_Qu8mg5v7(

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

 Construct the covariance scatter matrix for a given arap energy
   Inputs:
     V  #V by Vdim list of initial domain positions
     F  #F by 3 list of triangle indices into V
     energy  ARAPEnergyType enum value defining which energy is being used.
       See ARAPEnergyType.h for valid options and explanations.
   Outputs:
     CSM dim*#V/#F by dim*#V sparse matrix containing special laplacians along
       the diagonal so that when multiplied by V gives covariance matrix
       elements, can be used to speed up covariance matrix computation
)igl_Qu8mg5v7";

npe_function(covariance_scatter_matrix)
npe_doc(ds_covariance_scatter_matrix)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(energy, igl::ARAPEnergyType)


npe_begin_code()

  Eigen::SparseMatrix<double> & csm;
  igl::covariance_scatter_matrix(v, f, energy, csm);
  return npe::move(csm);

npe_end_code()


